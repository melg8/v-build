#ifndef V_BUILD_GLOBAL_H
#define V_BUILD_GLOBAL_H

#include <stdlib.h>

#define RUN_SHELL_LOOP for (;;)

// main definitions
#define COMMON_TEXT_SIZE 128
#define PLUGIN_LIST_SIZE 256

// main config
#define IO_INDEX 0
#define IO_PLUGIN_NAME "io"

typedef void (*void_func)();
typedef char *(*char_func)();

#endif // V_BUILD_GLOBAL_H
