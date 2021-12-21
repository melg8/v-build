#include "user_input_parser.h"

#include <stdio.h>
#include <string.h>

#include "io.h"

char user_args_etalon[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};
char user_input_args[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};
size_t cnt = 0;
bool is_input_correct = false;

void exec_plugin_command(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL) {
    print_info_msg(ERROR_MSG, "Strange behaviour, command not found", YES);
    return;
  }

  if (is_elem_binary(elem)) {

    voidfunc f = get_binary_function(cmd);

    if (is_func_has_args(elem)) {

      char *str = elem->descriptor.args;
      parse_args(str);

      while (!is_input_correct) {
        get_func_args();
        check_func_args();
      }
    } else {
      // run without args
    }
  }
}

void parse_args(const char *elem_args) {
  char copy[COMMON_TEXT_SIZE];
  strcpy(copy, elem_args);
  char delim[] = ",";
  char *p = NULL;

  p = strtok(copy, delim);

  // find all args
  while (p != NULL) {
    strcpy(user_args_etalon[cnt], p);
    p = strtok(NULL, delim);
    cnt++;
  }

  // remove whitespaces in args, if any exists
  for (size_t i = 0; i < cnt; ++i) {
    char temp[COMMON_TEXT_SIZE] = {0};
    strcpy(temp, user_args_etalon[i]);
    size_t spnz = strspn(temp, " ");
    strcpy(user_args_etalon[i], temp + spnz);
  }
}

bool is_func_has_args(const plugin_element *elem) {
  bool has_args = strcmp(elem->descriptor.args, NO_ARGS) != 0;
  return has_args;
}

void get_func_args() {
  char arg_type_must_be[COMMON_TEXT_SIZE] = {0};

  if (cnt == 0)
    return;

  for (size_t i = 0; i < cnt; ++i) {
    char it[10] = {0};
    sprintf(it, "%d", i);
    strcpy(arg_type_must_be, "Enter the argument ");
    strcat(arg_type_must_be, it);
    strcat(arg_type_must_be, " must be ");
    strcat(arg_type_must_be, user_args_etalon[i]);
    strcat(arg_type_must_be, "): ");

    char *arg_value = get_input(arg_type_must_be);
    strcpy(user_input_args[i], arg_value);

    memset(arg_type_must_be, 0, sizeof(arg_type_must_be));
  }
}

void check_func_args() {
  for (size_t i = 0; i < cnt; ++i) {
    if (strlen(user_input_args[i]) == 0) {
      print_info_msg(ERROR_MSG, "length of arg = 0!", YES);
    }
  }
}

void reset_user_args() {
  // reset input data
  memset(user_args_etalon, 0, sizeof(user_args_etalon));
  memset(user_input_args, 0, sizeof(user_input_args));
  is_input_correct = false;
  cnt = 0;
}

bool is_all_numbers(const char *array) {}
