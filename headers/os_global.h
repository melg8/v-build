#ifndef OS_GLOBAL_H
#define OS_GLOBAL_H

// main definitions
#define SHELL_NAME "shell: "
#define USER_COMMAND_LEN 64
#define ERROR_TEXT_LEN 256
#define SHELL_CMD_COUNT 512
#define SLEEP_MSEC 8000

// colors for output
#define OS_COLOR_RED "\x1b[31m"
#define OS_COLOR_GREEN "\x1b[32m"
#define OS_COLOR_YELLOW "\x1b[33m"
#define OS_COLOR_BLUE "\x1b[34m"
#define OS_NO_COLOR "\x1b[0m"

// common functions
#define CLEAR_SCREEN system("clear")
#define RUN_SHELL_LOOP for (;;)

// commands
#define INVALID_COMMAND                                                        \
  "invalid command, run \"help\" to view list of commands."

#endif // OS_GLOBAL_H
