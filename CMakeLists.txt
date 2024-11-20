cmake_minimum_required(VERSION 3.28)

project(ReverseShell)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  include_directories(src/linux)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  include_directories(src/win)
endif()

add_subdirectory(src)

add_executable(main main.c)
target_link_libraries(main PRIVATE shell)
