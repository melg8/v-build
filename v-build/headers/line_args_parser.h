#ifndef LINE_ARGS_PARSER_H
#define LINE_ARGS_PARSER_H

#include <stdbool.h>

#include "column_args_parser.h"
#include "plugin.h"
#include "plugin_parser.h"

char *get_command_from_line(const char *restrict cmd_line);
bool fill_line_args(const plugin_element *restrict elem);

bool is_parse_line_ok();
char *get_line_arg(size_t idx);

#endif // LINE_ARGS_PARSER_H
