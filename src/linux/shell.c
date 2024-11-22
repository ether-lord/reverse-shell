#include "shell.h"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

static int socket_fd;
static int connection_fd;

int shell_init(void) {
  struct sockaddr_in server_sockaddr_in;

  server_sockaddr_in.sin_family = AF_INET;
  server_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);

  const int port = PORT;
  server_sockaddr_in.sin_port = htons(port);

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  int bind_result = bind(socket_fd, (struct sockaddr *)&server_sockaddr_in,
                         sizeof(server_sockaddr_in));

  if (bind_result != 0) {
    perror("bind() failed");
    close(socket_fd);
    return -1;
  }

  listen(socket_fd, 10);

  struct sockaddr_in client_sockaddr_in;
  socklen_t len = sizeof(client_sockaddr_in);

  connection_fd =
      accept(socket_fd, (struct sockaddr *)&client_sockaddr_in, &len);

  char connection_ip_str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(client_sockaddr_in.sin_addr), connection_ip_str,
            INET_ADDRSTRLEN);

  const char* new_connection_str = "New connection from: ";
  write(connection_fd, new_connection_str, strlen(new_connection_str));
  write(connection_fd, connection_ip_str, strlen(connection_ip_str));
  write(connection_fd, "\n", 1);
  write(connection_fd, ">", 1);

  return connection_fd;
}

int shell_get_socket_fd(void) { return socket_fd; }

void shell_shutdown_connection(void) {
  const char* connection_shutdown_msg = "Shuting down the connection\n";
  write(connection_fd, connection_shutdown_msg, strlen(connection_shutdown_msg));
  close(socket_fd);
  shutdown(socket_fd, SHUT_RDWR);
}
