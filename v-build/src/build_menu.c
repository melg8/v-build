#include "build_menu.h"

#include <stdio.h>
#include <string.h>

#include "io.h"

bool is_build_menu(const char *cmd) {
  if (strcmp(cmd, "build") == 0) {
    return true;
  }
  return false;
}

void run_build_menu() { print_info_msg(COMPLETE, "inside build menu", YES); }
