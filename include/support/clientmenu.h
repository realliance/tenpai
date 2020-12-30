#pragma once

#include <any>
#include "support/menu.h"

namespace Support {
  namespace ClientMenu {
    auto buildMenu() -> Support::Menu;
    auto localPlay(std::any& param) -> void;
    auto networkPlay(std::any& param) -> void;
  }
}
