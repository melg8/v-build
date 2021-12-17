#ifndef IO_H
#define IO_H

#include "plugin.h"
#include "v_build_global.h"

// default io funcs
extern void (*greetings)();
extern void (*print_help)();

// 0 is success, -1 is error
int load_io();

#endif // IO_H
