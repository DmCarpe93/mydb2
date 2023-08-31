#include "common/connection/tcp_connection.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace common {

void TcpConnection::Connect(std::string address, uint16_t port) {
  tcp::endpoint endpoint(boost::asio::ip::address::from_string(address), port);
  try {
    socket_.connect(endpoint);
  } catch (const boost::system::system_error &error) {
    std::cerr << "Error: " << error.what() << std::endl;
  }
}

void TcpConnection::Accept(uint16_t port) {
  if (!acceptor_.get()) {
    tcp::endpoint endpoint(tcp::v4(), port);
    acceptor_ = std::make_unique<tcp::acceptor>(io_context_, endpoint);
  }
  acceptor_->accept(socket_);
}

void TcpConnection::AsyncAccept(uint16_t port, AsyncAcceptHandler handler) {
  if (!acceptor_.get()) {
    tcp::endpoint endpoint(tcp::v4(), port);
    acceptor_ = std::make_unique<tcp::acceptor>(io_context_, endpoint);
  }
  acceptor_->async_accept(socket_, handler);
}

std::size_t TcpConnection::ReadSome() {
  boost::system::error_code error;
  std::size_t bytes_transferred =
      socket_.read_some(boost::asio::buffer(buffer_, kMaxBufferSize), error);
  if (!error) {
    std::cout << "Received: "
              << std::string(buffer_, buffer_ + bytes_transferred) << std::endl;
  } else {
    std::cerr << "Error while reading: " << error.message() << std::endl;
  }
  return bytes_transferred;
}

void TcpConnection::Write(const char *data, int data_len) {
  boost::asio::write(socket_, boost::asio::buffer(data, data_len));
}

void TcpConnection::AsyncRead(AsyncReadHandler handler) {
  socket_.async_receive(boost::asio::buffer(buffer_), handler);
}

void TcpConnection::AsyncReadSome(AsyncReadHandler handler) {
  socket_.async_read_some(boost::asio::buffer(buffer_), handler);
}

} // namespace common