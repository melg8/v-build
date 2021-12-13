#ifndef OS_GLOBAL_H
#define OS_GLOBAL_H

#include <stdlib.h>

// main definitions
#define SHELL_NAME "shell: "
#define USER_COMMAND_LEN 128
#define ERROR_TEXT_LEN 256
#define SLEEP_MSEC_COMMON 7000
#define SLEEP_MSEC_HELP 500
#define HELP_STRING_LENGTH 1024 * 1024
#define MSG_LENGTH 512
#define YES 1
#define NO 0

// file names
#define CONFIG_FILE ".v-build.config"

// colors for output
#define OS_COLOR_RED "\x1B[31m"
#define OS_COLOR_GREEN "\x1B[32m"
#define OS_COLOR_YELLOW "\x1B[33m"
#define OS_COLOR_BLUE "\x1B[34m"
#define OS_NO_COLOR "\x1B[0m"

#define SHELL_TITILE OS_COLOR_GREEN SHELL_NAME OS_NO_COLOR

// msg titles
#define INFO_MSG OS_COLOR_BLUE "info: " OS_NO_COLOR
#define ERROR_MSG OS_COLOR_RED "err: " OS_NO_COLOR
#define COMPLETE OS_COLOR_GREEN "complete: " OS_NO_COLOR
#define QUESTION OS_COLOR_YELLOW "question: " OS_NO_COLOR

// common functions
#define CLEAR_SCREEN system("clear")
#define RUN_SHELL_LOOP for (;;)
#define EXIT(code) exit(code)

// commands
#define INVALID_COMMAND                                                        \
  "invalid command, run \"help\" to view list of commands."
#define NOT_IMPLEMENTED "command is simple, but not implemented yet."
#define YES_NO_INCORRECT_INPUT "please enter Y,YES,y,yes or N,NO,n,no."

#endif // OS_GLOBAL_H
