#ifndef SHELL_HELPER_H
#define SHELL_HELPER_H

#include <stddef.h>

// 0 - success, -1 is error
void exec_help_command(const char *cmd);

// print loaded plugins
void print_loaded_functions();

// list of all file.plug located in plugins dir
void view_all_plugins();

void print_incorrect_expected_values(size_t cur_idx,
                                     const char *restrict expected_value,
                                     const char *entered_value);

#endif // SHELL_HELPER_H
