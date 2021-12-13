#include "shell.h"
#include "plugin.h"

int main(void) {

  check_plugins();
  run_shell();

  return 0;
}
