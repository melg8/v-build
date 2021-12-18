#include "io.h"

#include <stdio.h>

#define FUNC_COUNT 4

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();
void (*print_help)();
void (*print_info_msg)();

void _get_io_funcs();

int load_io() {
  if (load_plugin(IO_PLUGIN_NAME) == -1) {
    printf("%s: plugin loading error, exit.\n", IO_PLUGIN_NAME);
    return -1;
  } else {
  }

  return 0;
}

void _get_io_funcs() { greetings = get_command("greetings"); }
