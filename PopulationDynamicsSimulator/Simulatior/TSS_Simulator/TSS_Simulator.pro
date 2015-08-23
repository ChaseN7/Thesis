#-------------------------------------------------
#
# Project created by QtCreator 2014-08-14T19:59:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TSS_Simulator
TEMPLATE = app
CONFIG += c++11


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
