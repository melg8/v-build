TEMPLATE = app

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
        src/text_processing/text_processor.c \
        src/shell/shell.c

HEADERS += \
        headers/os_global.h \
        headers/text_processing/text_processor.h \
        headers/shell/shell.h


