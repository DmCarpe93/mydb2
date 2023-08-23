#include "frame/connection/ipc_connection.h"
#include "frame/process/process.h"

namespace frame {

class WorkerProcess : public Process {
public:
  WorkerProcess() : ipc_conn_(io_context_) {
    /* TODO: Make Thread Pool */
    /* Accept IPC connection from listener process */
    std::string conn_path = "listener_path";
    ipc_conn_.Accept(conn_path);
    AsyncWaitForNewConnection();
  }

  void Run() override {
    try {
      io_context_.run();
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

private:
  void AsyncWaitForNewConnection();
  void HandleNewConnection();

  boost::asio::io_context io_context_;
  IpcConnection ipc_conn_;
};

} // namespace frame
