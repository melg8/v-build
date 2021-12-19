#include "autoload.h"
#include "shell.h"

int main(int argc, char *argv[]) {

  (void)argc;
  (void)argv;

  autoload_plugins();

  run_shell();

  return 0;
}
