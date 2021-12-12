#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include <stdbool.h>

#include "command_checks.h"

bool is_command_exist(const char *cmd);
bool is_command_simple(const char *cmd);

size_t find_command(const char *cmd);

char *get_command_from_user();

void print_help_msg();

void print_info_msg(const char *title, const char *color, const char *msg);
void print_msg(const char *msg, size_t sleep_msec);

#endif // TEXT_PROCESSING_H
