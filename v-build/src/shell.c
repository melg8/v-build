#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void (*greetings)();
void (*print_help)();

void run_shell() {
  obtain_io();

  print_help();
  // RUN_SHELL_LOOP {}
}

void obtain_io() {
  char path[COMMON_TEXT_SIZE];

  try_to_load_plugin(IO_PLUGIN_PATH);
  construct_path(path, IO_INDEX);

  if (open_binary(path) == 0) {
    print_help = get_func(IO_INDEX);
  } else {
    exit(EXIT_FAILURE);
  }
}

void try_to_load_plugin(const char *plugin_path) {
  if (load_plugin(plugin_path) == -1) {
    printf("plugin loading error, exit.\n");
    exit(EXIT_FAILURE);
  }
}
