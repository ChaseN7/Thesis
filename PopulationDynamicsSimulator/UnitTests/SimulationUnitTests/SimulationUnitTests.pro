#-------------------------------------------------
#
# Project created by QtCreator 2014-08-14T19:57:16
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_simulationunitteststest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += tst_simulationunitteststest.cpp \
    ../../Simulatior/TSS_Simulator/eventclass.cpp \
    ../../Simulatior/TSS_Simulator/filestreaming.cpp \
    ../../Simulatior/TSS_Simulator/graphclass.cpp \
    ../../Simulatior/TSS_Simulator/randomdice.cpp \
    ../../Simulatior/TSS_Simulator/traitclass.cpp \
    ../../Simulatior/TSS_Simulator/traiteventmanager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../Simulatior/TSS_Simulator/eventclass.h \
    ../../Simulatior/TSS_Simulator/filestreaming.h \
    ../../Simulatior/TSS_Simulator/graphclass.h \
    ../../Simulatior/TSS_Simulator/randomdice.h \
    ../../Simulatior/TSS_Simulator/traitclass.h \
    ../../Simulatior/TSS_Simulator/traiteventmanager.h

FORMS += \
    ../../Simulatior/TSS_Simulator/mainwindow.ui \
    ../../Simulatior/TSS_Simulator/plotwindow.ui
