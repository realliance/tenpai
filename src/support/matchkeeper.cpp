#include "support/matchkeeper.h"

#include <algorithm>

using namespace Support;

auto MatchKeeper::RecordScores(gameScores scoreList) -> void {  
  matchScores.push_back(scoreList);

  auto winnerIndex = std::distance(scoreList.begin(), std::max_element(scoreList.begin(), scoreList.end()));
  winner[winnerIndex]++;
}
