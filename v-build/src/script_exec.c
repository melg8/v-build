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
  int ret_val = 0;

  char script_path[COMMON_TEXT_SIZE] = {0};
  char script_name[COMMON_TEXT_SIZE] = {0};

  strcpy(script_path, elem->descriptor.exec);
  strcpy(script_name, elem->descriptor.command);
  strcat(script_name, ".sh");

  int pid = fork();

  if (pid == 0) {
    if (_cmd_arg_counter == 0) {
      ret_val = execl(script_path, script_name, NULL);
    }

    if (_cmd_arg_counter == 1) {
      ret_val = execl(script_path, script_name, user_input_args[0], NULL);
    }

    if (ret_val == -1) {
      strerror(errno);
    } else {
      char ret_ch[COMMON_TEXT_SIZE];
      sprintf(ret_ch, "%d", ret_val);
      print_info_msg(RETURN_VAL, ret_ch, YES);
    }
  } else if (pid != 0 || pid != -1) {
    wait(NULL);
  } else {
    strerror(errno);
  }
}
