#ifndef TEXT_GLOBAL_H
#define TEXT_GLOBAL_H

#include <stdlib.h>

// main definitions
#define SHELL "shell: "
#define SUBSHELL "subshell: "
#define USER_COMMAND_LEN 256
#define SLEEP_MSEC_COMMON 500
#define SLEEP_MSEC_FAST 50
#define HELP_STRING_LENGTH 1024 * 128
#define MSG_LENGTH 512
#define YES 1
#define NO 0

// colors for output
#define OS_COLOR_RED "\x1B[31m"
#define OS_COLOR_GREEN "\x1B[32m"
#define OS_COLOR_YELLOW "\x1B[33m"
#define OS_COLOR_BLUE "\x1B[34m"
#define OS_NO_COLOR "\x1B[0m"

#define SHELL_TITILE OS_COLOR_GREEN SHELL OS_NO_COLOR
#define SUBSHELL_TITILE OS_COLOR_BLUE SUBSHELL OS_NO_COLOR

// msg titles
#define INFO_MSG OS_COLOR_BLUE "info: " OS_NO_COLOR
#define ERROR_MSG OS_COLOR_RED "err: " OS_NO_COLOR
#define COMPLETE OS_COLOR_GREEN "complete: " OS_NO_COLOR
#define QUESTION OS_COLOR_YELLOW "question: " OS_NO_COLOR

// common functions
#define EXIT(code) exit(code)

// commands

#define YES_NO_INCORRECT_INPUT "please enter (Y,YES,y,yes) || (N,NO,n,no)."

// common sizes
#define COMMON_TEXT_SIZE 256
#define PLUGIN_LIST_SIZE 1024

// key arrows
#define ARROW_UP "UP"
#define ARROW_DOWN "DOWN"
#define ARROW_LEFT "LEFT"
#define ARROW_RIGHT "RIGHT"

#endif // TEXT_GLOBAL_H
