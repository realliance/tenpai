#pragma once

#include <map>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <mutex>
#include "playercontroller.h"

namespace Support {
  class MatchKeeper {
    using gameScores = std::vector<uint16_t>;

    private:
      MatchKeeper() {
        winner.resize(4);
        std::fill(winner.begin(), winner.end(), 0);
      }
    public:
      static MatchKeeper& getInstance() {
        static MatchKeeper instance;
        return instance;
      }

      std::mutex scoreMutex;
      std::vector<gameScores> matchScores;
      std::vector<uint8_t> winner;
      uint32_t currentMatches;
      uint32_t totalMatches;

      auto ConfigureMatchNum(uint32_t m) -> void { currentMatches = 0; totalMatches = m; }
      auto RecordScores(gameScores scores) -> void;
      auto PrintProgress() -> void;


      MatchKeeper(MatchKeeper const&) = delete;
      void operator=(MatchKeeper const&)  = delete;
  };
}
