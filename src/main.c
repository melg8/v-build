#include "plugin.h"
#include "shell.h"

int main(int argc, char *argv[]) {

  (void)argc;
  (void)argv;

  load_common_plugin();
  run_shell();

  return 0;
}
