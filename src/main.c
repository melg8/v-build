#include "shell.h"
#include "config.h"

int main(void) {

  check_config();
  run_shell();

  return 0;
}
