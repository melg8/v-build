#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include <stdbool.h>

#include "text_creation.h"

void greetings();
void print_help_msg();

void print_msg(const char *msg, size_t sleep_msec);
void print_info_msg(const char *title, const char *msg, int newline_symbol);

// 1 - answer received, 0 - no
int ask_yes_no(const char *question_text);

bool is_command_exist(const char *cmd);

char *get_command_from_user(bool is_title_needed);

#endif // TEXT_PROCESSING_H
