#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "shell.h"

#define MAX_MESSAGE_SIZE 1024

int main(void) {
  int connection_fd = shell_init();
  if (connection_fd == -1) return -1;

  while (1) {
    int bytes_received = shell_recieve();
    const char* buffer = shell_get_buffer();

    if (bytes_received == 0 || buffer[0] == '\n') continue;
    printf("%.*s", bytes_received, buffer);

    EShellCommands shell_command = shell_handle_input();

    switch (shell_command) {
      case UNKNOWN:
        break;
      case QUIT:
        shell_shutdown_connection();
        return 0;
        break;
      default:
        break;
    }

    char status = 0;
    write(connection_fd, &status, 1);
    send(connection_fd, ">", 1, 0);
  }

  return 0;
}