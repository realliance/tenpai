
#include "gentlemanbot.h"

#include "support/menu.h"
#include "support/clientmenu.h"

using Support::Params;
using Support::ClientMenu::buildMenu;

int main() {

  std::any param = Params {};

  buildMenu().menu(param);

  return 0;
}
