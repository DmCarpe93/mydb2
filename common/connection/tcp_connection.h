#ifndef COMMON_TPC_CONNECTION_H
#define COMMON_TPC_CONNECTION_H

#include "common/connection/connection.h"
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace common {

class TcpConnection : public Connection {
public:
  static constexpr std::size_t kMaxBufferSize = 8192;
  using AsyncAcceptHandler =
      std::function<void(const boost::system::error_code &)>;
  using AsyncReadHandler =
      std::function<void(const boost::system::error_code &, std::size_t)>;

  TcpConnection(boost::asio::io_context &io_context)
      : Connection(), io_context_(io_context), socket_(io_context_) {}
  virtual ~TcpConnection() {}

  tcp::socket &Socket() { return socket_; }
  void Connect(std::string address, uint16_t port);

  void Accept(uint16_t port);
  void AsyncAccept(uint16_t port, AsyncAcceptHandler handler);
  int Release() { return socket_.release(); }
  std::size_t ReadSome();
  void Write(const char *data, int data_len);

  void Assign(int native_socket) {
    socket_.assign(boost::asio::ip::tcp::v4(), native_socket);
  }
  void AsyncRead(AsyncReadHandler handler);
  void AsyncReadSome(AsyncReadHandler handler);

  const char *Buffer() { return buffer_; }

private:
  boost::asio::io_context &io_context_;
  tcp::socket socket_;
  std::unique_ptr<tcp::acceptor> acceptor_;
  char buffer_[kMaxBufferSize];
};

} // namespace common

#endif