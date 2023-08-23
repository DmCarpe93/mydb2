#include "frame/connection/connection.h"
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace frame {

class TcpConnection : public Connection {
public:
  static constexpr std::size_t kMaxBufferSize = 8192;
  using AsyncAcceptHandler =
      std::function<void(const boost::system::error_code &)>;

  TcpConnection(boost::asio::io_context &io_context)
      : Connection(), io_context_(io_context), socket_(io_context_) {}
  virtual ~TcpConnection() {}

  tcp::socket &Socket() { return socket_; }
  void Connect(uint16_t peer_port) {}

  void Accept(uint16_t port);
  void AsyncAccept(uint16_t port, AsyncAcceptHandler handler);
  int Release() { return socket_.release(); }
  std::size_t ReadSome();
  void Assign(int native_socket) {
    socket_.assign(boost::asio::ip::tcp::v4(), native_socket);
  }

private:
  boost::asio::io_context &io_context_;
  tcp::socket socket_;
  std::unique_ptr<tcp::acceptor> acceptor_;
  char buffer_[kMaxBufferSize];
};

} // namespace frame
