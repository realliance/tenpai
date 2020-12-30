#include "support/menu.h"

#include <iostream>
#include <any>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>
#include <optional>
#include <sstream>
#include <limits>
#include <cctype>

#include "controllermanager.h"

using namespace Support;

using Mahjong::GetAvailableControllers;

std::optional<std::string> Input::getline(std::istream& is, const std::string& def) {
  for (auto no = is.rdbuf()->in_avail(); no && is && std::isspace(is.peek()); is.ignore(), --no);

  std::string ln;

  return std::getline(is, ln) ? (ln.empty() && !def.empty() ? def : ln) : (is.clear(), std::optional<std::string> {});
};

std::string Input::getline(const std::string& prm, const std::string& def) {
  std::optional<std::string> o;

  do {
    std::cout << prm;
    if (!def.empty())
      std::cout << " [" << def << "]";

    std::cout << " : ";
    o = getline(std::cin, def);
  } while (!o.has_value() && (std::cout << "Invalid input" << std::endl));

  return *o;
};

std::string Input::getbotselection(const std::string& message) {
  auto botList = GetAvailableControllers();
  std::ostringstream oss;

  oss << '\n';

  int i = 0;
  for (const auto& botName : botList) {
    oss << "[" << i << "] " << botName << '\n';
    i++;
  }

  std::cout << oss.str() << '\n';
  return botList[Input::getnum(message, 0, i - 1)];
}
