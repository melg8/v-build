TEMPLATE = app

TARGET = v-build

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0 -rdynamic
QMAKE_LIBDIR_FLAGS += -ldl

INCLUDEPATH += \
        $$PWD/src \
        $$PWD/headers

SOURCES += \
    src/autoload.c \
    src/bin_parser.c \
    src/io.c \
        src/main.c \
        src/plugin.c \
    src/plugin_bin_exec.c \
        src/plugin_parser.c \
        src/shell.c \
    src/shell_helper.c

HEADERS += \
        headers/autoload.h \
        headers/bin_parser.h \
        headers/io.h \
        headers/plugin.h \
        headers/plugin_bin_exec.h \
        headers/plugin_parser.h \
        headers/shell.h \
        headers/shell_helper.h \
        headers/v_build_global.h

DISTFILES += \
    ../plugins/io.plug \
    ../plugins/autoload.config \
    ../to_do


