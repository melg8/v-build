#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void run_shell() {
  RUN_SHELL_LOOP {
    get_input_from_user();
  }
}
