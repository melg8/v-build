#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();
// end

void _get_io_funcs();

void _obtain_io();

void run_shell() {
  _obtain_io();

  greetings();
  // RUN_SHELL_LOOP {}
}

// it is default binary
void _obtain_io() {
  char path[COMMON_TEXT_SIZE];

  try_to_load_plugin(IO_PLUGIN_PATH);
  get_plugin_path(path, IO_INDEX);

  if (open_binary(path) == 0) {
    _get_io_funcs();
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

void _get_io_funcs() { greetings = get_func(0); }
