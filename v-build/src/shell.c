#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void run_shell() {
  if (load_io() != 0) {
    printf("error loading io plugin\n");
    exit(EXIT_FAILURE);
  }

  ask_yes_no("everything alright?");
}
