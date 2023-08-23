#include "frame/process/worker_process.h"
#include "frame/connection/tcp_connection.h"
#include <iostream>
#include <memory>

void SetBlocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    perror("fcntl - F_GETFL");
    return;
  }

  if (fcntl(fd, F_SETFL, flags & ~O_NONBLOCK) == -1) {
    perror("fcntl - F_SETFL");
    return;
  }
}

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
  ::iovec io = {.iov_base = m_buffer, .iov_len = IpcConnection::kMaxBufferSize};
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
  SetBlocking(client_fd);
  TcpConnection conn(io_context_);
  conn.Assign(client_fd);
  /* TODO: Deliver client fd to worker thread*/
  conn.ReadSome();
  /*
  char buffer[8192];
  int readlen;
  while ((readlen = ::read(client_fd, buffer, 8192)) > 0) {
    buffer[readlen] = '\0';
    std::cout << buffer << std::endl;
  }
  */
}

} // namespace frame
