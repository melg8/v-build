TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

VPATH += \
        $$PWD/src \
        $$PWD/src/shell \
        $$PWD/src/text_processor \
        $$PWD/headers \
        $$PWD/headers/shell \
        $$PWD/headers/text_processor

SOURCES += \
        main.c \
        text_processor.c \
        shell.c

HEADERS += \
        text_processor.h \
        shell.h


