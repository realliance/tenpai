#include "action.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <thread>

#include "bots/viewer.h"

#include "support/matchkeeper.h"
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
using Support::MatchKeeper;

auto Action::connectToNetworkGame(std::string url, std::string botName) -> void {
  auto selectedBot = GetController(botName);
  auto bot = selectedBot();
  connectToMatch(*bot, url);
}

auto Action::startLocalGame(uint32_t matches, std::string botA, std::string botB, std::string botC, std::string botD) -> void {
  std::vector<std::string> botList = {botA, botB, botC, botD};

  auto createViewer = [&botList]() -> PlayerController* { return new Viewer(GetController(botList[0]), botList); };
  if (!RegisterController(createViewer, "Viewer")) {
    std::cerr << "Error: Failed to create Viewer Handler" << std::endl;
    return;
  }

  for (uint32_t i = 0; i < matches; i++) {
    StartGame({{ "Viewer", botB, botC, botD }}, false);
  }

  std::ostringstream oss;

  oss << std::endl;
  oss << "== " << matches << " Matches Complete ==" << std::endl;

  uint8_t o = 0;
  for (const auto& score : MatchKeeper::getInstance().winner) {
    oss << botList[o] << " Wins: " << std::to_string(score) << std::endl;
    o++;
  }

  std::cout << oss.str();
}
