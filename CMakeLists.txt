cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
project(gametablesdkdemo)

find_package(spdlog REQUIRED)

add_subdirectory(${gametablesdkdemo_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME})

ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(libmahjong PRIVATE -pedantic -Wall -Wmost -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(libmahjong PRIVATE -pedantic -Wall -Wextra)
endif()

add_subdirectory(${gametablesdkdemo_SOURCE_DIR}/src)

get_target_property(gametablesdkdemo_sources gametablesdkdemo SOURCES)

target_include_directories(${PROJECT_NAME} PUBLIC "${gametablesdkdemo_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} libmahjong)
target_link_libraries(${PROJECT_NAME} gametablesdk)
