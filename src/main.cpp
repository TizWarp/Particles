#include "application.hpp"
#include "threads.hpp"
#include <cmath>
#include <cstdio>
int main(){



  ThreadPool thread_pool;
  thread_pool.start();

  Application app(&thread_pool);
  app.run();

  thread_pool.stop();
  return 0;
}
