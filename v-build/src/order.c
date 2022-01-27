#include "order.h"

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "io.h"
#include "line_args_parser.h"
#include "plugin.h"
#include "plugin_parser.h"

void exec_order_list() {
  print_info_msg(INFO_MSG, "under construction...", YES);
}
