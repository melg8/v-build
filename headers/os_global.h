#ifndef OS_GLOBAL_H
#define OS_GLOBAL_H

#define SHELL_NAME "shell: "

#define USER_COMMAND_LEN 64

// colors for output
#define OS_COLOR_RED "\x1b[31m"
#define OS_COLOR_GREEN "\x1b[32m"
#define OS_COLOR_YELLOW "\x1b[33m"
#define OS_COLOR_BLUE "\x1b[34m"
#define OS_NO_COLOR "\x1b[0m"

// common functions
#define CLEAR_SCREEN system("clear")
#define RUN_SHELL_LOOP for (;;)

#endif // OS_GLOBAL_H
