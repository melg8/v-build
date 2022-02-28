#ifndef BUILD_MENU_H
#define BUILD_MENU_H

#include "v_build_global.h"

bool is_build_menu(const char *cmd);

void run_build_menu();

void run_build_cmd();
void prepare_toolchain_x86_64();
void start_build_toolchain_x86_64();

#endif // BUILD_MENU_H
