#include "common/connection/ipc_connection.h"
#include "common/message/message.pb.h"
#include "frame/process/process.h"
#include "frame/thread/thread_pool.h"
#include "frame/thread/worker_thread.h"
#include <iostream>

namespace common {
class TcpConnection;
}

namespace frame {

class WorkerProcess : public Process {
public:
  WorkerProcess() : ipc_conn_(io_context_), thread_pool_(10) {
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
  void AsyncReceiveUserRequest(std::shared_ptr<common::TcpConnection> conn);
  void HandleUserRequest(const common::Message &message);

  boost::asio::io_context io_context_;
  common::IpcConnection ipc_conn_;
  std::vector<std::shared_ptr<common::TcpConnection>> client_connections_;
  ThreadPool<WorkerThread> thread_pool_;
};

} // namespace frame
