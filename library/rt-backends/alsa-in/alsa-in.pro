TEMPLATE = lib
CONFIG += plugin
static {
    CONFIG += staticlib create_prl
}
TARGET = $$qtLibraryTarget(drumstick-rt-alsa-in)
DESTDIR = ../../../build/lib/drumstick
DEPENDPATH += . ../../include
INCLUDEPATH += . ../../include
include (../../../global.pri)
QT -= gui

HEADERS += ../../include/rtmidiinput.h \
           ../../include/rtmidioutput.h \
           alsamidiinput.h
SOURCES += alsamidiinput.cpp

LIBS += -L../../../build/lib \
        -l$$qtLibraryTarget(drumstick-alsa) \
        -lasound
