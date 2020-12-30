#include "support/clientmenu.h"
#include "support/menu.h"

#include "action.h"

#include <string>
#include <vector>
#include <any>

using namespace Support;

using Action::connectToNetworkGame,
      Action::startLocalGame;

auto ClientMenu::buildMenu() -> Support::Menu {
  return {"GameTable Client", {{"Network Play", &networkPlay}, {"Local Play", &localPlay}}};
}

auto ClientMenu::networkPlay(std::any& param) -> void {
  auto& v = std::any_cast<Params&>(param);

  std::string url = Input::getline("Enter GameTable Server URL");
  std::string botName = Input::getbotselection();

  connectToNetworkGame(url, botName);
}

auto ClientMenu::localPlay(std::any& param) -> void {
  auto& v = std::any_cast<Params&>(param);

  std::string botA = Input::getbotselection("Select Bot #1");
  std::string botB = Input::getbotselection("Select Bot #2");
  std::string botC = Input::getbotselection("Select Bot #3");
  std::string botD = Input::getbotselection("Select Bot #4");
  uint32_t matches = Input::getnum<uint32_t>("Number of Matches", 1, 4294967294);
  
  startLocalGame(matches, botA, botB, botC, botD);
}
