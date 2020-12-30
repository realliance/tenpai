set(DIR ${CMAKE_CURRENT_LIST_DIR})

target_sources(${PROJECT_NAME}
  PRIVATE
  "${DIR}/bots/templatebot.h"
  "${DIR}/support/menu.h"
  "${DIR}/support/clientmenu.h"
  "${DIR}/action.h"
  "${DIR}/bots/viewer.h"
  "${DIR}/support/matchkeeper.h"
  "${DIR}/support/matchpool.h"
)
