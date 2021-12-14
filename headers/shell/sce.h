#ifndef SCE_H
#define SCE_H

#include <stdbool.h>
#include <stddef.h>

#include "v_build_global.h"

// SCE - Simple Command Execution

void run_sc(const char *cmd);

bool is_help();
bool is_quit();
bool is_clear();

#endif // SCE_H
