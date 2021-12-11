#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include <stdbool.h>

#include "command_checks.h"

bool is_command_exist(const char *cmd);
char *get_command_from_user();

void print_help_msg();
void error_msg(const char *msg);
void write_msg(const char *msg);

#endif // TEXT_PROCESSING_H
