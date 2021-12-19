#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void run_shell() {
  load_io();

  ask_yes_no("everything alright?");
}
