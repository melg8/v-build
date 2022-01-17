TEMPLATE = lib

TARGET = navigation_lib

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0 -rdynamic

INCLUDEPATH += $$PWD

SOURCES += \
        navigation.c

HEADERS += \
        navigation.h

