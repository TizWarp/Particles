#include "threads.hpp"
#include "SFML/System/Thread.hpp"
#include "particle.hpp"
#include <cstdint>
#include <functional>
#include <mutex>
#include <thread>
#include <type_traits>

void ThreadPool::Start(){
  const uint32_t num_threads = std::thread::hardware_concurrency();
  for (uint32_t ii = 0; ii < num_threads; ii++){
    threads.emplace_back(std::thread(&ThreadPool::ThreadLoop,this));
  }
}

void ThreadPool::ThreadLoop(){
  while(true){
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      mutex_condition.wait(lock, [this]{
          return !jobs.empty() || should_close;
          });
      if (should_close){
        return;
      }
      job = jobs.front();
      jobs.pop();
    }
    job();
  }
}

void ThreadPool::QueueJob(const std::function<void()>& job){
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    jobs.push(job);
  }
  mutex_condition.notify_all();
}

bool ThreadPool::busy(){
  bool poolBusy;
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    poolBusy = !jobs.empty();
  }
  return poolBusy;
}

void ThreadPool::Stop(){
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    should_close = true;
  }
  mutex_condition.notify_all();
  for (std::thread &active_thread : threads){
    active_thread.join();
  }
  threads.clear();
}
