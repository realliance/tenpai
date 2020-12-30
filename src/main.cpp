
#include <controllermanager.h>

#include "bots/templatebot.h"

#include "support/menu.h"
#include "support/clientmenu.h"

using Support::Params,
      Support::ClientMenu::buildMenu;

using Mahjong::RegisterController;

int main() {

  // Register Local Bots
  RegisterController([]() { return new TemplateBot; }, "TemplateBot");

  // Launch Menus
  std::any param = Params {};
  buildMenu().menu(param);

  return 0;
}
