#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T22:23:53
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_traiteventmanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_traiteventmanagertest.cpp \
    randomdice.cpp \
    traiteventmanager.cpp \
    eventclass.cpp \
    traitclass.cpp \
    filestreaming.cpp \
    graphclass.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    randomdice.h \
    traiteventmanager.h \
    eventclass.h \
    traitclass.h \
    filestreaming.h \
    graphclass.h

QMAKE_CXXFLAGS += -std=c++11
