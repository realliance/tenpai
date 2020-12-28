FetchContent_Declare(
  libmahjong
  GIT_REPOSITORY https://github.com/realliance/libmahjong.git
  GIT_TAG        fdb7dc06c71656781ba1f17aa7eb174fd6f4fb76
)

FetchContent_GetProperties(libmahjong)
if(NOT libmahjong_POPULATED)
  FetchContent_Populate(libmahjong)
  add_subdirectory(${libmahjong_SOURCE_DIR} ${libmahjong_BINARY_DIR})
endif()

FetchContent_Declare(
  gametablesdk
  GIT_REPOSITORY https://github.com/realliance/gametable-sdk.git
  GIT_TAG        ac88427be73ecbbfd635533fa7b9a212ecb9397c
)

FetchContent_GetProperties(gametablesdk)
if(NOT gametablesdk_POPULATED)
  FetchContent_Populate(gametablesdk)
  add_subdirectory(${gametablesdk_SOURCE_DIR} ${gametablesdk_BINARY_DIR})
endif()
