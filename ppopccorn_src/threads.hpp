#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <queue>

class ThreadPool {


public:
  void Start();
  void Stop();
  bool busy();
  void QueueJob(const std::function<void()>& job);

private :
  bool should_close = false;
  std::vector<std::thread> threads;
  std::mutex queue_mutex;
  std::condition_variable mutex_condition;
  std::queue<std::function<void()>> jobs;
  
  void ThreadLoop();

};
