#include "io.h"

#include <stdio.h>

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();

void _get_io_funcs();

int load_io() {
  if (load_plugin(IO_PLUGIN_NAME) == -1) {
    printf("%s: plugin loading error, exit.\n", IO_PLUGIN_NAME);
    return -1;
  }

  return 0;
}
