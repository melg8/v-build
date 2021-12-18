#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include <stdbool.h>

#include "text_creation.h"

void greetings();
void print_help_msg();

void print_msg(const char *msg, size_t sleep_msec);
void print_info_msg(const char *title, const char *msg, int newline_symbol);
int ask_yes_no(const char *question_text);

bool is_command_exist(const char *cmd);
bool is_command_simple(const char *cmd);

size_t find_command(const char *cmd);

char *get_command_from_user();

#endif // TEXT_PROCESSING_H
