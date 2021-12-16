#include "plugin.h"
#include "shell.h"

int main(int argc, char *argv[]) {

  (void)argc;
  (void)argv;

  if (is_text_plugin_loaded()) {
    run_shell();
  }

  return 0;
}
