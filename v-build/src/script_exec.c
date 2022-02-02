#include "script_exec.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "io.h"
#include "plugin.h"
#include "v_build_global.h"

void exec_script(const plugin_element *elem) {

  char script_path[COMMON_TEXT_SIZE] = {0};

  strcpy(script_path, start_exec_dir);
  strcat(script_path, "/");
  strcat(script_path, elem->descriptor.exec);

  if (_cmd_arg_counter == 1) {
    strcat(script_path, " ");
    strcat(script_path, user_input_args[0]);
  }

  if (_cmd_arg_counter == 2) {
    strcat(script_path, " ");
    strcat(script_path, user_input_args[0]);
    strcat(script_path, " ");
    strcat(script_path, user_input_args[1]);
  }

  if (_cmd_arg_counter == 3) {
    strcat(script_path, " ");
    strcat(script_path, user_input_args[0]);
    strcat(script_path, " ");
    strcat(script_path, user_input_args[1]);
    strcat(script_path, " ");
    strcat(script_path, user_input_args[2]);
  }

  system(script_path);
}
