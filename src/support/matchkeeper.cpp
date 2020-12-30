#include "support/matchkeeper.h"

#include <algorithm>
#include <thread>
#include <iostream>

using namespace Support;

auto MatchKeeper::RecordScores(gameScores scoreList) -> void {
  {
    std::unique_lock<std::mutex> lock(scoreMutex);
    matchScores.push_back(scoreList);
    auto winnerIndex = std::distance(scoreList.begin(), std::max_element(scoreList.begin(), scoreList.end()));
    winner[winnerIndex]++;

    currentMatches++;
  }
}

auto MatchKeeper::PrintProgress() -> void {
  uint8_t percentage;
  {
    percentage = ((float)currentMatches / totalMatches) * 100;
  }
  std::cout << "[" << std::to_string(percentage) << "%]  " << currentMatches << " / " << totalMatches << " Matches Completed" << std::endl;
}
