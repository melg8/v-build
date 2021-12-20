#ifndef SHELL_HELPER_H
#define SHELL_HELPER_H

// 0 - success, -1 is error
void exec_help_command(const char *cmd);

// print loaded plugins
void print_loaded_functions();

// list of all file.plug located in plugins dir
void view_all_plugins();

#endif // SHELL_HELPER_H
