#ifndef FRAME_WORKER_TASK_H
#include "frame/task/task.h"

namespace common {
class Message;
}

namespace frame {
class ConnectRequestTask : public Task {
public:
  ConnectRequestTask(const common::Message &message);
  virtual ~ConnectRequestTask() {}
  void Run() override;

private:
  std::string username_;
  std::string password_;
};

} // namespace frame
#endif