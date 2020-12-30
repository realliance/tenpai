#pragma once

#include <map>
#include <string>
#include <vector>
#include <random>
#include <map>
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

      std::vector<gameScores> matchScores;
      std::vector<uint8_t> winner;

      auto RecordScores(gameScores scores) -> void;


      MatchKeeper(MatchKeeper const&) = delete;
      void operator=(MatchKeeper const&)  = delete;
  };
}
