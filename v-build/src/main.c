#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "autoload.h"
#include "shell.h"
#include "v_build_global.h"

static char V_BUILD_SYSTEM[COMMON_TEXT_SIZE] = {"V_BUILD_SYSTEM="};

void define_vbuild_dir() {
  char curdir[COMMON_TEXT_SIZE] = {0};
  if (getcwd(curdir, COMMON_TEXT_SIZE) == NULL) {
    printf("Error putenv V_BUILD_SYSTEM: %s\n", strerror(errno));
    EXIT(EXIT_FAILURE);
  } else {
    strcat(V_BUILD_SYSTEM, curdir);
    strcat(V_BUILD_SYSTEM, "/system");
    putenv(V_BUILD_SYSTEM);
  }
}

int main(int argc, char *argv[]) {

  define_vbuild_dir();

  autoload_plugins();

  (void)argc;
  (void)argv;

  run_shell();

  return 0;
}
