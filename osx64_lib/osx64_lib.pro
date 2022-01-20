TEMPLATE = lib

TARGET = osx64_lib

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ggdb3 -O0 -rdynamic

INCLUDEPATH += $$PWD

SOURCES += \
		osx64.c

HEADERS += \
		osx64.h

