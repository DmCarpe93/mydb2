#include <iostream>

#include "common/message/message.pb.h"
#include "frame/task/worker_task.h"

namespace frame {

ConnectRequestTask::ConnectRequestTask(const common::Message &message)
    : Task(), username_(message.connect_request().username()),
      password_(message.connect_request().password()) {}

void ConnectRequestTask::Run() {
  std::cout << "username: " << username_ << std::endl;
  std::cout << "password: " << password_ << std::endl;
}
} // namespace frame