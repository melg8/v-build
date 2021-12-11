#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <stdbool.h>

#include "command_checker.h"

bool is_command_exist(const char *p);
char *get_command_from_user();

void print_help_msg(const struct cmd_triplet *instance);

void error_msg(const char *msg);

void write_msg(const char *msg);

#endif // TEXT_PROCESSOR_H
