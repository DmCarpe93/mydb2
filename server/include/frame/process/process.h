#ifndef FRAME_PROCESS_H
#define FRAME_PROCESS_H

namespace frame {
class Process {
public:
  Process() {}
  virtual ~Process() {}
  virtual void Run() = 0;
};

} // namespace frame
#endif