#ifndef SHELL_HELPER_H
#define SHELL_HELPER_H

#include <stdbool.h>
#include <stddef.h>

#include "v_build_global.h"
#include "plugin_parser.h"

extern global_conf g_conf;
extern pthread_t input_thread;
extern pthread_t err_thread;
extern pthread_rwlock_t rwlock;
extern void *user_input;

void set_internal_conf();
void unset_internal_conf();

char *get_user_input(int shell_type);
void print_err();

void exec_help_command(const char *cmd);
void exec_extra_command(const char *cmd);

// print loaded plugins
void print_loaded_functions();

// list of all file.plug located in plugins dir
void view_all_plugins();

void print_incorrect_expected_values(size_t cur_idx,
                                     const char *restrict expected_value,
                                     const char *entered_value);

void view_config();
void view_history();

bool is_extra_command(const char *cmd);

void add_cmd_to_history(const char *cmd, const plugin_element* elem);

#endif // SHELL_HELPER_H
