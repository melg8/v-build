#include "autoload.h"
#include "shell.h"

int main(int argc, char *argv[]) {

  autoload_plugins();

  (void)argc;
  (void)argv;

  run_shell();

  return 0;
}
