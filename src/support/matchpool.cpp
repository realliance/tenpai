#include "support/matchpool.h"

#include <thread>
#include <mutex>
#include <iostream>
#include <functional>

using namespace Support;

auto MatchPool::threadEntry() -> void {
  while(true) {
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(jobMutex);
      condition.wait(lock, [this]{ return !jobs.empty() || terminate; });
      if (terminate) {
        return;
      }
      job = jobs.back();
      jobs.pop_back();
    }
    job();
  }
}

MatchPool::MatchPool(uint16_t poolSize) {
  auto maxThreads = std::thread::hardware_concurrency();
  if (poolSize > maxThreads || poolSize == 0) {
    poolSize = maxThreads;
  }

  for (uint16_t i = 0; i < poolSize; i++) {
    pool.push_back(std::thread(&MatchPool::threadEntry, this));
  }
}

auto MatchPool::addJob(std::function<void()> job) -> void {
  {
    std::unique_lock<std::mutex> lock(jobMutex);
    jobs.push_back(job);
  }
  condition.notify_one();
}

auto MatchPool::shutdown() -> void {
  {
    std::unique_lock<std::mutex> lock(jobMutex);
    terminate = true;
  }
  condition.notify_all();

  for (auto& t : pool) {
    t.join();
  }

  terminate = false;
}
