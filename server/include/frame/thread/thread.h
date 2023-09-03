#ifndef FRAME_THREAD_H
#define FRAME_THREAD_H
#include <mutex>
#include <queue>
#include <thread>

namespace frame {
class Task;
class Thread {
public:
  Thread(std::mutex &m, std::condition_variable &cv,
         std::queue<std::unique_ptr<Task>> &tasks, bool &stop_all)
      : m_(m), cv_(cv), tasks_(tasks), stop_all_(stop_all),
        thread_([this] { this->Run(); }) {}
  virtual ~Thread() { thread_.join(); }
  virtual void Run() = 0;

protected:
  std::mutex &m_;
  std::condition_variable &cv_;
  std::queue<std::unique_ptr<Task>> &tasks_;
  bool &stop_all_;
  std::thread thread_;
};

} // namespace frame
#endif