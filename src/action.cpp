#include "action.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <thread>
#include <chrono>

#include "bots/viewer.h"

#include "support/matchkeeper.h"
#include "support/matchpool.h"
#include "controllermanager.h"
#include "settings.h"
#include "statefunctions.h"
#include "gametablesdk/network.h"

using Mahjong::GetController,
      Mahjong::RegisterController,
      Mahjong::newControllerInst,
      Mahjong::GameSettings,
      Mahjong::StartGame;
using GametableSDK::Network::connectToMatch;
using Support::MatchKeeper,
      Support::MatchPool;

auto Action::connectToNetworkGame(std::string url, std::string botName) -> void {
  auto selectedBot = GetController(botName);
  auto bot = selectedBot();
  connectToMatch(*bot, url);
}

auto Action::startLocalGame(uint32_t matches, uint32_t threads, std::string botA, std::string botB, std::string botC, std::string botD) -> void {
  std::vector<std::string> botList = {botA, botB, botC, botD};

  auto createViewer = [&botList]() -> PlayerController* { return new Viewer(GetController(botList[0]), botList); };
  if (!RegisterController(createViewer, "Viewer")) {
    std::cerr << "Error: Failed to create Viewer Handler" << std::endl;
    return;
  }

  MatchKeeper::getInstance().ConfigureMatchNum(matches);

  MatchPool pool(threads);

  for (uint32_t i = 0; i < matches; i++) {
    pool.addJob([&botB, &botC, &botD]() { StartGame({{ "Viewer", botB, botC, botD }}, false); });
  }

  while (pool.jobsRemaining()) {
    MatchKeeper::getInstance().PrintProgress();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  pool.shutdown();
  MatchKeeper::getInstance().PrintProgress();

  std::ostringstream oss;

  oss << std::endl;
  oss << "== " << matches << " Matches Complete ==" << std::endl;

  uint8_t o = 0;
  for (const auto& score : MatchKeeper::getInstance().winner) {
    oss << "Player " << o + 1 << " (" << botList[o] << ") Wins: " << std::to_string(score) << std::endl;
    o++;
  }

  std::cout << oss.str();
}
