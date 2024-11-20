if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(SHELL_SOURCES linux)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(SHELL_SOURCES win)
endif()

add_library(shell 
  ${SHELL_SOURCES}/shell.c
  ${SHELL_SOURCES}/shell.h
)
