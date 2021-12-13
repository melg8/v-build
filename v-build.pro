TEMPLATE = app

TARGET = v-build

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CCFLAG += -g

INCLUDEPATH += \
        $$PWD/src \
        $$PWD/src/shell \
        $$PWD/src/text_processing \
        $$PWD/headers \
        $$PWD/headers/shell \
        $$PWD/headers/text_processing

SOURCES += \
        src/main.c \
        src/plugin.c \
        src/shell/sce.c \
        src/text_processing/command_checks.c \
        src/shell/shell.c \
        src/text_processing/text_creation.c \
        src/text_processing/text_processing.c

HEADERS += \
        headers/os_global.h \
        headers/plugin.h \
        headers/shell/sce.h \
        headers/text_processing/command_checks.h \
        headers/text_processing/text_creation.h \
        headers/shell/shell.h \
        headers/text_processing/text_processing.h


