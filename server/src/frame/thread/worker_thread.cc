#include "frame/thread/worker_thread.h"
#include "frame/task/worker_task.h"

namespace frame {
void WorkerThread::Run() {
  while (true) {
    std::unique_lock<std::mutex> lock(m_);
    cv_.wait(lock, [this]() { return !this->tasks_.empty() || stop_all_; });
    if (stop_all_ && this->tasks_.empty()) {
      return;
    }

    auto task = std::move(tasks_.front());
    tasks_.pop();
    lock.unlock();

    task->Run();
  }
}

} // namespace frame