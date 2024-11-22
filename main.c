#include <string.h>

#include "shell.h"

#define MAX_MESSAGE_SIZE 1024

int main(void) {
  int connection_fd = shell_init();

  char buffer[MAX_MESSAGE_SIZE];

  while (1) {
    int buffer_len =
        recv(connection_fd, buffer, sizeof(buffer), 0);
    if (buffer_len == 0 || buffer[0] == '\n') continue;
    printf("%.*s", buffer_len, buffer);

    if (strstr(buffer, "q") != NULL) {
      close(shell_get_socket_fd());
      break;
    }

    char status = 0;
    write(connection_fd, &status, 1);
    send(connection_fd, ">", 1, 0);
  }

  return 0;
}