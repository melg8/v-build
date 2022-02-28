#ifndef V_BUILD_GLOBAL_H
#define V_BUILD_GLOBAL_H

#include <stdbool.h>
#include <stdlib.h>

#define SHELL 0
#define SUBSHELL 1

#define ARROW_UP "UP"
#define ARROW_DOWN "DOWN"
#define ARROW_LEFT "LEFT"
#define ARROW_RIGHT "RIGHT"

#define ARGS_COUNT 3

// main definitions
#define COMMON_TEXT_SIZE 256
#define PLUGIN_LIST_SIZE 256
#define RETURN_VALUE_SIZE 128

extern char user_args_etalon[ARGS_COUNT][COMMON_TEXT_SIZE];
extern char user_input_args[ARGS_COUNT][COMMON_TEXT_SIZE];
extern size_t _cmd_arg_counter;
extern bool _is_input_correct;
extern bool _is_args_ok;
extern bool _is_has_args;

// colors for output
#define OS_COLOR_RED "\x1B[31m"
#define OS_COLOR_GREEN "\x1B[32m"
#define OS_COLOR_YELLOW "\x1B[33m"
#define OS_COLOR_BLUE "\x1B[34m"
#define OS_NO_COLOR "\x1B[0m"

#define YES 1
#define NO 0

#define SHELL_NAME "shell: "
#define SHELL_TITILE OS_COLOR_GREEN SHELL_NAME OS_NO_COLOR

#define CLEAR_SCREEN system("clear")
#define EXIT(code) exit(code)

#define INVALID_COMMAND                                                        \
  "invalid command, run \"help\" to view list of commands."

// msg titles
#define INFO_MSG OS_COLOR_BLUE "info: " OS_NO_COLOR
#define ERROR_MSG OS_COLOR_RED "err: " OS_NO_COLOR
#define COMPLETE OS_COLOR_GREEN "complete: " OS_NO_COLOR
#define QUESTION OS_COLOR_YELLOW "question: " OS_NO_COLOR
#define AUTOLOAD OS_COLOR_YELLOW "autoload: " OS_NO_COLOR
#define RETURN_VAL OS_COLOR_YELLOW "return value: " OS_NO_COLOR
#define CONFIG_NAME(config_name) OS_COLOR_YELLOW " >>> " config_name OS_NO_COLOR
#define GREEN_YES OS_COLOR_GREEN "yes" OS_NO_COLOR
#define RED_NO OS_COLOR_RED "no" OS_NO_COLOR

#define SHELL_LOOP for (;;)

// main config
#define IO_INDEX 0
#define IO_PLUGIN_NAME "io"

typedef struct global_conf {
  bool is_column_args;
  bool is_line_args;
} global_conf;

extern global_conf g_conf;
extern char start_exec_dir[COMMON_TEXT_SIZE];

#endif // V_BUILD_GLOBAL_H
