TEMPLATE = app

TARGET = v-build

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0

INCLUDEPATH += \
        $$PWD/src \
        $$PWD/headers

SOURCES += \
        src/main.c \
        src/plugin.c \
        src/plugin_parser.c \
        src/sce.c \
        src/shell.c \

HEADERS += \
        headers/plugin.h \
        headers/plugin_parser.h \
        headers/sce.h \
        headers/shell.h \
        headers/v_build_global.h

DISTFILES += \
        ../plugins/common.plug


