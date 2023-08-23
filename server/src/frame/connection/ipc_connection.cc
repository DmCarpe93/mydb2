#include "frame/connection/ipc_connection.h"
#include <iostream>

namespace frame {

void IpcConnection::Accept(const std::string &path) {
  ::unlink(path.c_str());
  stream_protocol::endpoint endpoint(path);
  acceptor_ =
      std::make_unique<stream_protocol::acceptor>(io_context_, endpoint);
  acceptor_->accept(socket_);
}

void IpcConnection::Connect(const std::string &path) {
  boost::asio::local::stream_protocol::endpoint endpoint(path);
  try {
    socket_.connect(endpoint);
  } catch (const boost::system::system_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void IpcConnection::AsyncReadSome(AsyncReadHandler handler) {
  socket_.async_read_some(boost::asio::buffer(buffer_, kMaxBufferSize),
                          handler);
}

void IpcConnection::AsyncWait(boost::asio::socket_base::wait_type wait_type,
                              AsyncWaitHandler handler) {
  socket_.async_wait(wait_type, handler);
}

} // namespace frame