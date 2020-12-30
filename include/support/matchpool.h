#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <functional>

namespace Support {
  class MatchPool {
    private:
      std::mutex jobMutex;
      std::vector<std::function<void()>> jobs;
      bool terminate = false;
      std::condition_variable condition;
      std::vector<std::thread> pool;
      auto threadEntry() -> void;
    public:
      MatchPool(uint16_t poolSize);
      auto addJob(std::function<void()> job) -> void;
      auto shutdown() -> void;
      auto jobsRemaining() -> bool { return !jobs.empty(); }
  };
}
