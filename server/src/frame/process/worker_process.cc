#include "frame/process/worker_process.h"
#include "common/connection/tcp_connection.h"
#include "frame/task/task_builder.h"

#include <iostream>
#include <memory>

namespace frame {

void WorkerProcess::AsyncWaitForNewConnection() {
  ipc_conn_.AsyncWait(boost::asio::socket_base::wait_type::wait_read,
                      [this](const boost::system::error_code &error) {
                        if (error) {
                          std::cerr
                              << "Error in async wait: " << error.message()
                              << std::endl;
                        } else {
                          this->HandleNewConnection();
                          this->AsyncWaitForNewConnection();
                        }
                      });
}

void WorkerProcess::HandleNewConnection() {
  int client_fd;
  ::msghdr msg = {0};

  char *m_buffer = ipc_conn_.Buffer();
  ::iovec io = {.iov_base = m_buffer,
                .iov_len = common::IpcConnection::kMaxBufferSize};
  msg.msg_iov = &io;
  msg.msg_iovlen = 1;

  union {
    ::cmsghdr cmsghdr;
    char control[CMSG_SPACE(sizeof(int))];
  } cmsgu;
  msg.msg_control = &cmsgu;
  msg.msg_controllen = sizeof(cmsgu.control);

  auto size = ::recvmsg(ipc_conn_.Socket().native_handle(), &msg, 0);
  if (size < 0) {
    boost::system::error_code ec = {errno, boost::system::system_category()};
    std::cerr << "Send Client Socket Error: " << ec.message() << '\n';
    /* TODO: Deliver Error Message to Client */
    return;
  }
  ::cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
  unsigned char *data = CMSG_DATA(cmsg);
  std::memcpy(&client_fd, data, sizeof(client_fd));

  std::cout << "Get Connection from client" << std::endl;
  auto conn = std::make_shared<common::TcpConnection>(io_context_);
  conn->Assign(client_fd);
  client_connections_.push_back(conn);

  AsyncReceiveUserRequest(conn);
}

void WorkerProcess::AsyncReceiveUserRequest(
    std::shared_ptr<common::TcpConnection> conn) {
  conn->AsyncReadSome([this, conn](const boost::system::error_code &error,
                                   std::size_t bytes_transferred) {
    std::string serialized_msg(conn->Buffer(), bytes_transferred);
    common::Message message;
    if (!message.ParseFromString(serialized_msg)) {
      std::cerr << "Failed to deserialize the message." << std::endl;
      return;
    }
    this->HandleUserRequest(message);
    this->AsyncReceiveUserRequest(conn);
  });
}

void WorkerProcess::HandleUserRequest(const common::Message &message) {
  auto task = TaskBuilder::CreateTask(message);
  thread_pool_.EnqueueTask(std::move(task));
}

} // namespace frame
