TEMPLATE = app
TARGET = drumstick-dumpwrk
CONFIG += qt console link_prl
DESTDIR = ../../build/bin
INCLUDEPATH += . ../../library/include ../common 
LIBS = -L../../build/lib -ldrumstick-common -ldrumstick-file
PRE_TARGETDEPS += $$OUT_PWD/../../build/lib/libdrumstick-common.a
include (../../global.pri)
# Input
HEADERS += dumpwrk.h
SOURCES += dumpwrk.cpp
