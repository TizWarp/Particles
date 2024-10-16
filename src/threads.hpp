#pragma once

#include "defines.hpp"
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool{

  public:
    void start();
    void stop();
    bool busy();
    void queueJob(const std::function<void()>& job);

  private:
    bool should_stop;
    std::queue<std::function<void()>> jobs;
    std::condition_variable cond_var;
    std::mutex queue_mutex;
    std::vector<std::thread> threads;
    void threadLoop();
};
