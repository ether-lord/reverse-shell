#ifndef SHELL_H
#define SHELL_H

int shell_init(void);
int shell_get_socket_fd(void);
void shell_shutdown_connection(void);

#endif /* SHELL_H */
