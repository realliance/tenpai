set(DIR ${CMAKE_CURRENT_LIST_DIR})

target_sources(${PROJECT_NAME}
  PRIVATE
  "${DIR}/main.cpp"
  "${DIR}/bots/templatebot.cpp"
  "${DIR}/support/clientmenu.cpp"
  "${DIR}/support/menu.cpp"
  "${DIR}/action.cpp"
  "${DIR}/bots/viewer.cpp"
  "${DIR}/support/matchkeeper.cpp"
  "${DIR}/support/matchpool.cpp"
)
