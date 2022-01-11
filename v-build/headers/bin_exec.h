#ifndef BIN_EXEC_H
#define BIN_EXEC_H

#include "bin_parser.h"
#include "plugin.h"

typedef void (*void_f)();
typedef int (*int_f)();
typedef char *(*char_f)();
typedef bool (*bool_f)();

extern void_f fvoid;
extern int_f fint;
extern char_f fcharp;
extern bool_f fbool;

extern char *charp_args[ARGS_COUNT];
extern int int_args[ARGS_COUNT];
extern int bool_args[ARGS_COUNT];

extern const plugin_element *_elem;

void exec_bin(const plugin_element *elem);

#endif // BIN_EXEC_H
