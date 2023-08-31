#ifndef COMMON_IPC_CONNECTION_H
#define COMMON_IPC_CONNECTION_H

#include "common/connection/connection.h"
#include <boost/asio/local/stream_protocol.hpp>

using boost::asio::local::stream_protocol;

namespace common {

class IpcConnection : public Connection {
public:
  static constexpr std::size_t kMaxBufferSize = 8192;
  using AsyncReadHandler =
      std::function<void(const boost::system::error_code &, std::size_t)>;
  using AsyncWaitHandler =
      std::function<void(const boost::system::error_code &)>;

  IpcConnection(boost::asio::io_context &io_context)
      : Connection(), io_context_(io_context), socket_(io_context_),
        acceptor_(nullptr) {}
  virtual ~IpcConnection() {}

  stream_protocol::socket &Socket() { return socket_; }
  void Accept(const std::string &path);
  void Connect(const std::string &path);

  void AsyncReadSome(AsyncReadHandler handler);
  void AsyncWait(boost::asio::socket_base::wait_type wait_type,
                 AsyncWaitHandler handler);
  char *Buffer() { return buffer_; }

private:
  boost::asio::io_context &io_context_;
  stream_protocol::socket socket_;
  std::unique_ptr<stream_protocol::acceptor> acceptor_;
  char buffer_[kMaxBufferSize];
};

} // namespace common

#endif