cmake_minimum_required(VERSION 3.28)

project(ReverseShell)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  include_directories(src/linux)
  add_subdirectory(src/linux)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  include_directories(src/win)
  add_subdirectory(src/win)
endif()


add_executable(main main.c)
target_link_libraries(main PRIVATE shell)
