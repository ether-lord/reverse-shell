#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 8192

typedef enum ShellCommands {
  UNKNOWN = -1,
  QUIT = 0
} EShellCommands;

int shell_init(void);
int shell_recieve(void);
int shell_handle_input(void);

void shell_shutdown_connection(void);

const char* shell_get_buffer(void);

#endif /* SHELL_H */
