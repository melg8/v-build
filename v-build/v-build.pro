TEMPLATE = app

TARGET = v-build

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0 -rdynamic -pthread
QMAKE_LIBDIR_FLAGS += -ldl -lpthread

INCLUDEPATH += \
        $$PWD/src \
        $$PWD/headers

SOURCES += \
        src/autoload.c \
        src/bin_exec.c \
        src/bin_exec_internal.c \
        src/build_menu.c \
        src/column_args_parser.c \
        src/io.c \
        src/line_args_parser.c \
        src/main.c \
        src/plugin.c \
        src/plugin_parser.c \
        src/script_exec.c \
        src/shell.c \
        src/shell_helper.c \
        src/order.c \
        src/subshell.c

HEADERS += \
        headers/autoload.h \
        headers/bin_exec.h \
        headers/bin_exec_internal.h \
        headers/build_menu.h \
        headers/column_args_parser.h \
        headers/io.h \
        headers/line_args_parser.h \
        headers/plugin.h \
        headers/plugin_parser.h \
        headers/script_exec.h \
        headers/shell.h \
        headers/shell_helper.h \
        headers/subshell.h \
        headers/v_build_global.h \
        headers/order.h

DISTFILES += \
        ../system/autoload.config \
        ../system/io.plug \
        ../system/navigation.plug \
        ../system/osx64.plug \
        ../system/kernel.plug \
        ../system/order.list \
        ../to_do


