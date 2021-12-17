#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void run_shell() {
  if (load_io() != 0) {
    exit(EXIT_FAILURE);
  }

  greetings();
  // RUN_SHELL_LOOP {}
}
