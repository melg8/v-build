#include "shell.h"

#include <stdio.h>
#include <string.h>

#include "bin_exec.h"
#include "column_args_parser.h"
#include "io.h"
#include "line_args_parser.h"
#include "script_exec.h"
#include "shell_helper.h"
#include "subshell.h"
#include "v_build_global.h"

void run_shell() {
  // must be 1st line. load i/o library
  load_io();

  set_internal_conf();

  SHELL_LOOP {
    user_input = get_user_input();

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else if (is_subshell_command(user_input)) {
      run_subshell();
    } else {
      print_err();
    }
  }

  unset_internal_conf();
}
