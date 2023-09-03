#ifndef FRAME_WORKER_THREAD_H
#define FRAME_WORKER_THREAD_H

#include "frame/thread/thread.h"

namespace frame {
class WorkerThread : public Thread {
public:
  WorkerThread(std::mutex &m, std::condition_variable &cv,
               std::queue<std::unique_ptr<Task>> &tasks, bool &stop_all)
      : Thread(m, cv, tasks, stop_all) {}
  virtual ~WorkerThread() {}
  virtual void Run() override;

private:
  int worker_id_;
};

} // namespace frame
#endif