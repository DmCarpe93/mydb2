#ifndef FRAME_THREAD_POOL_H
#define FRAME_THREAD_POOL_H

#include "frame/task/task.h"
#include "frame/task/worker_task.h"
#include "frame/thread/thread.h"
#include <future>
#include <queue>

namespace frame {

template <typename T> class ThreadPool {
public:
  ThreadPool(size_t num_threads) : num_threads_(num_threads) {
    threads_.reserve(num_threads_);
    for (size_t i = 0; i < num_threads_; ++i) {
      threads_.push_back(std::make_unique<T>(m_, cv_, tasks_, stop_all));
    }
  };

  ~ThreadPool() {
    stop_all = true;
    cv_.notify_all();
  };

  void EnqueueTask(std::unique_ptr<Task> task) {
    {
      std::scoped_lock<std::mutex> lock(m_);
      tasks_.emplace(std::move(task));
    }
    cv_.notify_one();
  }

private:
  size_t num_threads_;
  std::mutex m_;
  std::condition_variable cv_;
  std::queue<std::unique_ptr<Task>> tasks_;
  std::vector<std::unique_ptr<Thread>> threads_;
  bool stop_all;
};

} // namespace frame
#endif