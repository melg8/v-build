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

  strcpy(script_path, exec_dir);
  strcat(script_path, "/");
  strcat(script_path, elem->descriptor.exec);

  if (_cmd_arg_counter == 0) {
    system(script_path);
  }
}
