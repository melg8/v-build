TEMPLATE = app

TARGET = v-build

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CCFLAG += -g

INCLUDEPATH += \
        $$PWD/src \
        $$PWD/src/shell \
        $$PWD/src/plugins \
        $$PWD/src/text_processing \
        $$PWD/headers \
        $$PWD/headers/shell \
        $$PWD/headers/text_processing \
        $$PWD/headers/plugins

SOURCES += \
        src/main.c \
        src/plugins/plugin.c \
        src/plugins/plugin_parser.c \
        src/shell/sce.c \
        src/text_processing/command_checks.c \
        src/shell/shell.c \
        src/text_processing/text_creation.c \
        src/text_processing/text_processing.c

HEADERS += \
        headers/plugins/plugin.h \
        headers/plugins/plugin_parser.h \
        headers/shell/sce.h \
        headers/text_processing/command_checks.h \
        headers/text_processing/text_creation.h \
        headers/shell/shell.h \
        headers/text_processing/text_processing.h \
        headers/v_build_global.h

DISTFILES += \
        plugins/common.plug


