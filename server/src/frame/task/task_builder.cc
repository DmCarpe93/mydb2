#include "frame/task/task_builder.h"
#include "common/message/message.pb.h"
#include "frame/task/worker_task.h"

namespace frame {

std::unique_ptr<Task> TaskBuilder::CreateTask(const common::Message &message) {
  auto message_type = message.type();
  if (message_type == common::MessageType::CONNECT_REQUEST) {
    return std::make_unique<ConnectRequestTask>(message);
  } else {
    std::cerr << "Create Task Error: Invalid Message Type" << std::endl;
  }
}

} // namespace frame