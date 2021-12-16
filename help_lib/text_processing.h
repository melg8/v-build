#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include <stdbool.h>

#include "text_creation.h"

bool is_command_exist(const char *cmd);
bool is_command_simple(const char *cmd);

size_t find_command(const char *cmd);

char *get_command_from_user(const char *text_before);

void print_help_msg();

void print_info_msg(const char *title, const char *msg, int newline_symbol);
void print_msg(const char *msg, size_t sleep_msec);

int ask_yes_no(const char *question_text);

#endif // TEXT_PROCESSING_H
