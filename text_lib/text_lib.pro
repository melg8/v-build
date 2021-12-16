TEMPLATE = lib

TARGET = text_lib

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0

INCLUDEPATH += $$PWD

SOURCES += \
        text_creation.c \
        text_processing.c

HEADERS += \
        text_creation.h \
        text_processing.h \
        text_global.h


