#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void run_shell() {
  RUN_SHELL_LOOP {
    char *user_input = get_input_f();
    if (arg_bool_f(user_input)) {
      printf("good\n");
    } else {
      printf("bad\n");
    }
  }
}
