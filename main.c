#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_MESSAGE_SIZE 1024

int main(int argc, char** argv) {
  int port = 0;

  // reading command line options
  int opt = 0;
  while ((opt = getopt(argc, argv, "p:")) != -1) {
    switch (opt) {
      case 'p':
        port = atoi(optarg);
        break;
      default:
        break;
    }
  }

  if (port <= 0) {
    printf("error: port argument is invalid\n");
    printf("hint: specify the port using \'-p\' option\n");
    return -1;
  }

  int connection_fd = shell_init(port);
  if (connection_fd == -1) return -1;

  while (1) {
    int bytes_received = shell_recieve();
    const char* buffer = shell_get_buffer();
    if (bytes_received == 0 || buffer[0] == '\n') continue;

    EShellCommands shell_command = shell_handle_input();

    switch (shell_command) {
      case UNKNOWN:
        printf("Couldn't recognize the input: %.*s", bytes_received, buffer);
        break;
      case QUIT:
        shell_shutdown_connection();
        return 0;
        break;
      default:
        break;
    }

    write(connection_fd, ">", 1);
  }

  return 0;
}