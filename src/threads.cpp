#include "threads.hpp"
#include "SFML/System/Thread.hpp"
#include <functional>
#include <mutex>
#include <thread>
#include "defines.hpp"

void ThreadPool::threadLoop(){
  while (true){
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      cond_var.wait(lock, [this]{
          return !jobs.empty() || should_stop;
          });
      if (should_stop){
        return;
      }
      job = jobs.front();
      jobs.pop();
    }
    job();
  }
}

void ThreadPool::queueJob(const std::function<void()>& job){
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    jobs.push(job);
  }
  cond_var.notify_all();
}

bool ThreadPool::busy(){
  bool poolBusy;
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    poolBusy = !jobs.empty();
  }
  return poolBusy;
}

void ThreadPool::stop(){
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    should_stop = true;
  }
  cond_var.notify_all();
  for (std::thread &active_thread : threads){
    active_thread.join();
  }
  threads.clear();
}

void ThreadPool::start(){
  const u32 thread_count = std::thread::hardware_concurrency();
  for (u32 ii = 0; ii < thread_count; ii++){
    threads.emplace_back(std::thread(&ThreadPool::threadLoop,this));
  }
}
