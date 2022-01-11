#include "bin_exec_internal.h"

#include <stdbool.h>
#include <stdio.h>

#include "io.h"

#define ISCH(x) ({ is_arg_charp(x); })
#define ISINT(x) ({ is_arg_int(x); })
#define ISBOOL(x) ({ is_arg_bool(x); })

#define VOID_EXEC1()                                                           \
  ({                                                                           \
    if (ISCH(0)) {                                                             \
      fvoid(charp_args[0]);                                                    \
    }                                                                          \
                                                                               \
    if (ISINT(0)) {                                                            \
      fvoid(int_args[0]);                                                      \
    }                                                                          \
                                                                               \
    if (ISBOOL(0)) {                                                           \
      fvoid(bool_args[0]);                                                     \
    }                                                                          \
  })

#define VOID_EXEC2()                                                           \
  ({                                                                           \
    /*charp*/                                                                  \
    if (ISCH(0) && ISCH(1)) {                                                  \
      fvoid(charp_args[0], charp_args[1]);                                     \
    }                                                                          \
                                                                               \
    if (ISCH(0) && ISINT(1)) {                                                 \
      fvoid(charp_args[0], int_args[1]);                                       \
    }                                                                          \
                                                                               \
    if (ISCH(0) && ISBOOL(1)) {                                                \
      fvoid(charp_args[0], bool_args[1]);                                      \
    }                                                                          \
    /*int*/                                                                    \
    if (ISINT(0) && ISCH(1)) {                                                 \
      fvoid(int_args[0], charp_args[1]);                                       \
    }                                                                          \
                                                                               \
    if (ISINT(0) && ISINT(1)) {                                                \
      fvoid(int_args[0], int_args[1]);                                         \
    }                                                                          \
                                                                               \
    if (ISINT(0) && ISBOOL(1)) {                                               \
      fvoid(int_args[0], bool_args[1]);                                        \
    }                                                                          \
    /*bool*/                                                                   \
    if (ISBOOL(0) && ISCH(1)) {                                                \
      fvoid(bool_args[0], charp_args[1]);                                      \
    }                                                                          \
                                                                               \
    if (ISBOOL(0) && ISINT(1)) {                                               \
      fvoid(bool_args[0], int_args[1]);                                        \
    }                                                                          \
                                                                               \
    if (ISBOOL(0) && ISBOOL(1)) {                                              \
      fvoid(bool_args[0], bool_args[1]);                                       \
    }                                                                          \
  })

#define VOID_EXEC3()                                                           \
  ({                                                                           \
    /*               CHARP            */                                       \
    if (ISCH(0) && ISCH(1) && ISCH(2)) {                                       \
      fvoid(charp_args[0], charp_args[1], charp_args[2]);                      \
    }                                                                          \
    if (ISCH(0) && ISCH(1) && ISINT(2)) {                                      \
      fvoid(charp_args[0], charp_args[1], int_args[2]);                        \
    }                                                                          \
    if (ISCH(0) && ISCH(1) && ISBOOL(2)) {                                     \
      fvoid(charp_args[0], charp_args[1], bool_args[2]);                       \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISCH(0) && ISINT(1) && ISCH(2)) {                                      \
      fvoid(charp_args[0], int_args[1], charp_args[2]);                        \
    }                                                                          \
    if (ISCH(0) && ISINT(1) && ISINT(2)) {                                     \
      fvoid(charp_args[0], int_args[1], int_args[2]);                          \
    }                                                                          \
    if (ISCH(0) && ISINT(1) && ISBOOL(2)) {                                    \
      fvoid(charp_args[0], int_args[1], bool_args[2]);                         \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISCH(0) && ISBOOL(1) && ISCH(2)) {                                     \
      fvoid(charp_args[0], bool_args[1], charp_args[2]);                       \
    }                                                                          \
    if (ISCH(0) && ISBOOL(1) && ISINT(2)) {                                    \
      fvoid(charp_args[0], bool_args[1], int_args[2]);                         \
    }                                                                          \
    if (ISCH(0) && ISBOOL(1) && ISBOOL(2)) {                                   \
      fvoid(charp_args[0], bool_args[1], bool_args[2]);                        \
    }                                                                          \
                                                                               \
    /*               INT             */                                        \
    if (ISINT(0) && ISCH(1) && ISCH(2)) {                                      \
      fvoid(int_args[0], charp_args[1], charp_args[2]);                        \
    }                                                                          \
    if (ISINT(0) && ISCH(1) && ISINT(2)) {                                     \
      fvoid(int_args[0], charp_args[1], int_args[2]);                          \
    }                                                                          \
    if (ISINT(0) && ISCH(1) && ISBOOL(2)) {                                    \
      fvoid(int_args[0], charp_args[1], bool_args[2]);                         \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISINT(0) && ISINT(1) && ISCH(2)) {                                     \
      fvoid(int_args[0], int_args[1], charp_args[2]);                          \
    }                                                                          \
    if (ISINT(0) && ISINT(1) && ISINT(2)) {                                    \
      fvoid(int_args[0], int_args[1], int_args[2]);                            \
    }                                                                          \
    if (ISINT(0) && ISINT(1) && ISBOOL(2)) {                                   \
      fvoid(int_args[0], int_args[1], bool_args[2]);                           \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISINT(0) && ISBOOL(1) && ISCH(2)) {                                    \
      fvoid(int_args[0], bool_args[1], charp_args[2]);                         \
    }                                                                          \
    if (ISINT(0) && ISBOOL(1) && ISINT(2)) {                                   \
      fvoid(int_args[0], bool_args[1], int_args[2]);                           \
    }                                                                          \
    if (ISINT(0) && ISBOOL(1) && ISBOOL(2)) {                                  \
      fvoid(int_args[0], bool_args[1], bool_args[2]);                          \
    }                                                                          \
                                                                               \
    /*               BOOL            */                                        \
    if (ISBOOL(0) && ISCH(1) && ISCH(2)) {                                     \
      fvoid(bool_args[0], charp_args[1], charp_args[2]);                       \
    }                                                                          \
    if (ISBOOL(0) && ISCH(1) && ISINT(2)) {                                    \
      fvoid(bool_args[0], charp_args[1], int_args[2]);                         \
    }                                                                          \
    if (ISBOOL(0) && ISCH(1) && ISBOOL(2)) {                                   \
      fvoid(bool_args[0], charp_args[1], bool_args[2]);                        \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISBOOL(0) && ISINT(1) && ISCH(2)) {                                    \
      fvoid(bool_args[0], int_args[1], charp_args[2]);                         \
    }                                                                          \
    if (ISBOOL(0) && ISINT(1) && ISINT(2)) {                                   \
      fvoid(bool_args[0], int_args[1], int_args[2]);                           \
    }                                                                          \
    if (ISBOOL(0) && ISINT(1) && ISBOOL(2)) {                                  \
      fvoid(bool_args[0], int_args[1], bool_args[2]);                          \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISBOOL(0) && ISBOOL(1) && ISCH(2)) {                                   \
      fvoid(bool_args[0], bool_args[1], charp_args[2]);                        \
    }                                                                          \
    if (ISBOOL(0) && ISBOOL(1) && ISINT(2)) {                                  \
      fvoid(bool_args[0], bool_args[1], int_args[2]);                          \
    }                                                                          \
    if (ISBOOL(0) && ISBOOL(1) && ISBOOL(2)) {                                 \
      fvoid(bool_args[0], bool_args[1], bool_args[2]);                         \
    }                                                                          \
  })

#define EXEC1(retval, func)                                                    \
  ({                                                                           \
    if (ISCH(0)) {                                                             \
      retval = func(charp_args[0]);                                            \
    }                                                                          \
                                                                               \
    if (ISINT(0)) {                                                            \
      retval = func(int_args[0]);                                              \
    }                                                                          \
                                                                               \
    if (ISBOOL(0)) {                                                           \
      retval = func(bool_args[0]);                                             \
    }                                                                          \
    retval;                                                                    \
  })

#define EXEC2(retval, func)                                                    \
  ({                                                                           \
    /*charp*/                                                                  \
    if (ISCH(0) && ISCH(1)) {                                                  \
      retval = func(charp_args[0], charp_args[1]);                             \
    }                                                                          \
                                                                               \
    if (ISCH(0) && ISINT(1)) {                                                 \
      retval = func(charp_args[0], int_args[1]);                               \
    }                                                                          \
                                                                               \
    if (ISCH(0) && ISBOOL(1)) {                                                \
      retval = func(charp_args[0], bool_args[1]);                              \
    }                                                                          \
    /*int*/                                                                    \
    if (ISINT(0) && ISCH(1)) {                                                 \
      retval = func(int_args[0], charp_args[1]);                               \
    }                                                                          \
                                                                               \
    if (ISINT(0) && ISINT(1)) {                                                \
      retval = func(int_args[0], int_args[1]);                                 \
    }                                                                          \
                                                                               \
    if (ISINT(0) && ISBOOL(1)) {                                               \
      retval = func(int_args[0], bool_args[1]);                                \
    }                                                                          \
    /*bool*/                                                                   \
    if (ISBOOL(0) && ISCH(1)) {                                                \
      retval = func(bool_args[0], charp_args[1]);                              \
    }                                                                          \
                                                                               \
    if (ISBOOL(0) && ISINT(1)) {                                               \
      retval = func(bool_args[0], int_args[1]);                                \
    }                                                                          \
                                                                               \
    if (ISBOOL(0) && ISBOOL(1)) {                                              \
      retval = func(bool_args[0], bool_args[1]);                               \
    }                                                                          \
    retval;                                                                    \
  })

#define EXEC3(retval, func)                                                    \
  ({                                                                           \
    /*               CHARP            */                                       \
    if (ISCH(0) && ISCH(1) && ISCH(2)) {                                       \
      retval = func(charp_args[0], charp_args[1], charp_args[2]);              \
    }                                                                          \
    if (ISCH(0) && ISCH(1) && ISINT(2)) {                                      \
      retval = func(charp_args[0], charp_args[1], int_args[2]);                \
    }                                                                          \
    if (ISCH(0) && ISCH(1) && ISBOOL(2)) {                                     \
      retval = func(charp_args[0], charp_args[1], bool_args[2]);               \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISCH(0) && ISINT(1) && ISCH(2)) {                                      \
      retval = func(charp_args[0], int_args[1], charp_args[2]);                \
    }                                                                          \
    if (ISCH(0) && ISINT(1) && ISINT(2)) {                                     \
      retval = func(charp_args[0], int_args[1], int_args[2]);                  \
    }                                                                          \
    if (ISCH(0) && ISINT(1) && ISBOOL(2)) {                                    \
      retval = func(charp_args[0], int_args[1], bool_args[2]);                 \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISCH(0) && ISBOOL(1) && ISCH(2)) {                                     \
      retval = func(charp_args[0], bool_args[1], charp_args[2]);               \
    }                                                                          \
    if (ISCH(0) && ISBOOL(1) && ISINT(2)) {                                    \
      retval = func(charp_args[0], bool_args[1], int_args[2]);                 \
    }                                                                          \
    if (ISCH(0) && ISBOOL(1) && ISBOOL(2)) {                                   \
      retval = func(charp_args[0], bool_args[1], bool_args[2]);                \
    }                                                                          \
                                                                               \
    /*               INT             */                                        \
    if (ISINT(0) && ISCH(1) && ISCH(2)) {                                      \
      retval = func(int_args[0], charp_args[1], charp_args[2]);                \
    }                                                                          \
    if (ISINT(0) && ISCH(1) && ISINT(2)) {                                     \
      retval = func(int_args[0], charp_args[1], int_args[2]);                  \
    }                                                                          \
    if (ISINT(0) && ISCH(1) && ISBOOL(2)) {                                    \
      retval = func(int_args[0], charp_args[1], bool_args[2]);                 \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISINT(0) && ISINT(1) && ISCH(2)) {                                     \
      retval = func(int_args[0], int_args[1], charp_args[2]);                  \
    }                                                                          \
    if (ISINT(0) && ISINT(1) && ISINT(2)) {                                    \
      retval = func(int_args[0], int_args[1], int_args[2]);                    \
    }                                                                          \
    if (ISINT(0) && ISINT(1) && ISBOOL(2)) {                                   \
      retval = func(int_args[0], int_args[1], bool_args[2]);                   \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISINT(0) && ISBOOL(1) && ISCH(2)) {                                    \
      retval = func(int_args[0], bool_args[1], charp_args[2]);                 \
    }                                                                          \
    if (ISINT(0) && ISBOOL(1) && ISINT(2)) {                                   \
      retval = func(int_args[0], bool_args[1], int_args[2]);                   \
    }                                                                          \
    if (ISINT(0) && ISBOOL(1) && ISBOOL(2)) {                                  \
      retval = func(int_args[0], bool_args[1], bool_args[2]);                  \
    }                                                                          \
                                                                               \
    /*               BOOL            */                                        \
    if (ISBOOL(0) && ISCH(1) && ISCH(2)) {                                     \
      retval = func(bool_args[0], charp_args[1], charp_args[2]);               \
    }                                                                          \
    if (ISBOOL(0) && ISCH(1) && ISINT(2)) {                                    \
      retval = func(bool_args[0], charp_args[1], int_args[2]);                 \
    }                                                                          \
    if (ISBOOL(0) && ISCH(1) && ISBOOL(2)) {                                   \
      retval = func(bool_args[0], charp_args[1], bool_args[2]);                \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISBOOL(0) && ISINT(1) && ISCH(2)) {                                    \
      retval = func(bool_args[0], int_args[1], charp_args[2]);                 \
    }                                                                          \
    if (ISBOOL(0) && ISINT(1) && ISINT(2)) {                                   \
      retval = func(bool_args[0], int_args[1], int_args[2]);                   \
    }                                                                          \
    if (ISBOOL(0) && ISINT(1) && ISBOOL(2)) {                                  \
      retval = func(bool_args[0], int_args[1], bool_args[2]);                  \
    }                                                                          \
    /*sub*/                                                                    \
    if (ISBOOL(0) && ISBOOL(1) && ISCH(2)) {                                   \
      retval = func(bool_args[0], bool_args[1], charp_args[2]);                \
    }                                                                          \
    if (ISBOOL(0) && ISBOOL(1) && ISINT(2)) {                                  \
      retval = func(bool_args[0], bool_args[1], int_args[2]);                  \
    }                                                                          \
    if (ISBOOL(0) && ISBOOL(1) && ISBOOL(2)) {                                 \
      retval = func(bool_args[0], bool_args[1], bool_args[2]);                 \
    }                                                                          \
    retval;                                                                    \
  })

void exec_internal_void() { fvoid(); }

bool exec_internal_bool() { return fbool(); }

int exec_internal_int() { return fint(); }

char *exec_internal_charp() { return fcharp(); }

void exec_internal_void_args() {
  if (_cmd_arg_counter == 1) {
    VOID_EXEC1();
  }
  if (_cmd_arg_counter == 2) {
    VOID_EXEC2();
  }
  if (_cmd_arg_counter == 3) {
    VOID_EXEC3();
  }
}

char *exec_internal_ret_charp_with_args() {
  char *retval = 0;
  if (_cmd_arg_counter == 1) {
    retval = EXEC1(retval, fcharp);
  }
  if (_cmd_arg_counter == 2) {
    retval = EXEC1(retval, fcharp);
  }
  if (_cmd_arg_counter == 3) {
    retval = EXEC1(retval, fcharp);
  }
  return retval;
}

bool exec_internal_ret_bool_with_args() {
  bool retval = 0;
  if (_cmd_arg_counter == 1) {
    retval = EXEC1(retval, fbool);
  }
  if (_cmd_arg_counter == 2) {
    retval = EXEC1(retval, fbool);
  }
  if (_cmd_arg_counter == 3) {
    retval = EXEC1(retval, fbool);
  }
  return retval;
}

int exec_internal_ret_int_with_args() {
  int retval = 0;
  if (_cmd_arg_counter == 1) {
    retval = EXEC1(retval, fint);
  }
  if (_cmd_arg_counter == 2) {
    retval = EXEC1(retval, fint);
  }
  if (_cmd_arg_counter == 3) {
    retval = EXEC1(retval, fint);
  }
  return retval;
}
