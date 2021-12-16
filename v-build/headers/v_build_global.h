#ifndef V_BUILD_GLOBAL_H
#define V_BUILD_GLOBAL_H

#include <stdlib.h>

#define RUN_SHELL_LOOP for (;;)

// main definitions
#define COMMON_TEXT_SIZE 128
#define PLUGIN_LIST_SIZE 64

// main config
#define MAIN_PLUGIN "plugins/main.plug"

typedef void (*void_func)();
typedef char *(*char_func)();

#endif // V_BUILD_GLOBAL_H
