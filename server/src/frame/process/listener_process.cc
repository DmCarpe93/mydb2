#include "frame/process/listener_process.h"
#include <iostream>
#include <memory>

namespace frame {

void ListenerProcess::StartAccept() {
  conn_.AsyncAccept(
      listener_port_, [this](const boost::system::error_code &error) {
        if (!error) {
          std::cout << "Accepted a new connection." << std::endl;
          this->HandleAccept();
        } else {
          std::cerr << "Error while accepting " << error.message() << std::endl;
          /* TODO: Deliver Error Message to Client */
        }
      });
}

void ListenerProcess::HandleAccept() {
  /* send socket fd through unix domain socket */
  auto client_fd = conn_.Socket().native_handle();
  // auto client_fd = conn_.Release();
  ::msghdr msg{};
  union {
    ::cmsghdr cmsghdr;
    char control[CMSG_SPACE(sizeof(int))];
  } cmsgu;

  ::iovec io = {.iov_base = (void *)"", .iov_len = 1};
  msg.msg_iov = &io;
  msg.msg_iovlen = 1;
  msg.msg_control = cmsgu.control;
  msg.msg_controllen = sizeof(cmsgu.control);

  ::cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
  cmsg->cmsg_len = CMSG_LEN(sizeof(int));
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = SCM_RIGHTS;

  std::memcpy(CMSG_DATA(cmsg), &client_fd, sizeof(client_fd));
  auto size = ::sendmsg(ipc_conn_.Socket().native_handle(), &msg, 0);
  if (size < 0) {
    boost::system::error_code ec = {errno, boost::system::system_category()};
    std::cerr << "Send Client Socket Error: " << ec.message() << '\n';
    /* TODO: Deliver Error Message to Client */
  }
  conn_.Release();
  StartAccept();
}

} // namespace frame
