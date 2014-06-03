#-------------------------------------------------
#
# Project created by QtCreator 2014-06-03T11:17:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TSS_Simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eventclass.cpp \
    filestreaming.cpp \
    graphclass.cpp \
    plotwindow.cpp \
    qcustomplot.cpp \
    randomdice.cpp \
    traitclass.cpp \
    traiteventmanager.cpp

HEADERS  += mainwindow.h \
    eventclass.h \
    filestreaming.h \
    graphclass.h \
    plotwindow.h \
    qcustomplot.h \
    randomdice.h \
    traitclass.h \
    traiteventmanager.h

FORMS    += mainwindow.ui \
    plotwindow.ui

QMAKE_CXXFLAGS += -std=c++11
