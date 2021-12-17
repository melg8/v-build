#include "io.h"

#include <stdio.h>

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();

void _get_io_funcs();

int load_io() {
  char path[COMMON_TEXT_SIZE];

  if (load_plugin(IO_PLUGIN_PATH) == -1) {
    printf("%s: plugin loading error, exit.\n", IO_PLUGIN_PATH);
    return -1;
  }

  get_plugin_path(path, IO_INDEX);

  if (open_binary(path) == 0) {
    _get_io_funcs();
  } else {
    return -1;
  }

  return 0;
}

void _get_io_funcs() { greetings = get_func(0); }
