
cmake_minimum_required (VERSION 3.8)

list(APPEND GAME "main.cpp")




project ("App")

add_executable (CMP316Application  ${GAME})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMP316Application PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
