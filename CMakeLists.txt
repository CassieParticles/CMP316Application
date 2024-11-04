
cmake_minimum_required (VERSION 3.8)

list(APPEND GAME "Game/GameLoop.cpp")

list(APPEND GAME "main.cpp")


project ("App")

add_executable (App  ${GAME})

target_compile_options(App PUBLIC /sanitize=address)
target_link_options(App PUBLIC /sanitize=address)

add_subdirectory(Non-Reality-Engine)
target_link_libraries(App PUBLIC NonRealityEngine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET App PROPERTY CXX_STANDARD 20)
endif()


