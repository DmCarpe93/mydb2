#ifndef FRAME_TASK_H
#define FRAME_TASK_H

namespace frame {
class Task {
public:
  Task() {}
  virtual ~Task() {}
  virtual void Run() = 0;
};
} // namespace frame

#endif