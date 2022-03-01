TEMPLATE = lib

TARGET = arm64_lib

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0 -rdynamic

INCLUDEPATH += $$PWD

SOURCES += \
        arm64.c

HEADERS += \
        arm64.h

