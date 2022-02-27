#ifndef SUBSHELL_H
#define SUBSHELL_H

#include "bin_exec.h"
#include "column_args_parser.h"
#include "io.h"
#include "line_args_parser.h"
#include "script_exec.h"
#include "shell_helper.h"
#include "subshell.h"
#include "v_build_global.h"

bool is_subshell_command(const char *cmd);

void run_subshell();

void try_to_exec_plugin(const char *restrict user_input);

void run_plugin(const plugin_element *restrict elem);

#endif // SUBSHELL_H
