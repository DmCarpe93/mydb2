#include "frame/connection/ipc_connection.h"
#include "frame/connection/tcp_connection.h"
#include "frame/process/process.h"
#include <iostream>

namespace frame {

class ListenerProcess : public Process {
public:
  ListenerProcess(uint16_t listener_port)
      : Process(), listener_port_(listener_port), io_context_(),
        conn_(io_context_), ipc_conn_(io_context_) {
    /* Make IPC connection with worker process */
    std::string conn_path = "listener_path";
    ipc_conn_.Connect(conn_path);
    /* Accept connection from client */
    StartAccept();
  }
  void Run() override {
    try {
      io_context_.run();
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

private:
  void StartAccept();
  void HandleAccept();

  uint16_t listener_port_;
  boost::asio::io_context io_context_;
  TcpConnection conn_;
  IpcConnection ipc_conn_;
};

} // namespace frame
