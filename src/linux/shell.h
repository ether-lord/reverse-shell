#ifndef SHELL_H
#define SHELL_H

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

int shell_init(void);
int shell_get_socket_fd(void);

#endif /* SHELL_H */
