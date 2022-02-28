#include "io.h"

#include <stdio.h>

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();
void (*print_msg)();
void (*print_fmt_msg)();
void (*print_info_msg)();
int (*ask_yes_no)();
bool (*is_help_command)();
char *(*get_shell_input)();
char *(*get_subshell_input)();
char *(*get_input)();
// end io lib

void load_io() {
  greetings = get_binary_function("greetings");
  print_help = get_binary_function("print_help_msg");
  print_msg = get_binary_function("print_msg");
  print_fmt_msg = get_binary_function("print_fmt_msg");
  print_info_msg = get_binary_function("print_info_msg");
  ask_yes_no = get_binary_function("ask_yes_no");
  is_help_command = get_binary_function("is_help_command");
  get_shell_input = get_binary_function("get_shell_input");
  get_subshell_input = get_binary_function("get_subshell_input");
  get_input = get_binary_function("get_input");

  greetings();
}
