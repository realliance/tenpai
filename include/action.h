#pragma once

#include <string>

namespace Action {
  auto connectToNetworkGame(std::string url, std::string bot) -> void;
  auto startLocalGame(uint32_t matches, std::string botOne, std::string botTwo, std::string botThree, std::string botFour) -> void;
}
