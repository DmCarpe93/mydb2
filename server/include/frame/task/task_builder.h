#ifndef FRAME_TASK_BUILDER_H
#define FRAME_TASK_BUILDER_H

#include "frame/task/task.h"
#include <memory>

namespace common {
class Message;
}

namespace frame {
class TaskBuilder {
public:
  static std::unique_ptr<Task> CreateTask(const common::Message &message);
  TaskBuilder() = delete;
  ~TaskBuilder() = delete;
};

} // namespace frame

#endif