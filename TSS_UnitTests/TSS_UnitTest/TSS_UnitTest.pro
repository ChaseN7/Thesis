#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T22:33:44
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_TSS_unittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_TSS_unittesttest.cpp \
    eventclass.cpp \
    filestreaming.cpp \
    graphclass.cpp \
    randomdice.cpp \
    traitclass.cpp \
    traiteventmanager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    eventclass.h \
    filestreaming.h \
    graphclass.h \
    randomdice.h \
    traitclass.h \
    traiteventmanager.h

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
