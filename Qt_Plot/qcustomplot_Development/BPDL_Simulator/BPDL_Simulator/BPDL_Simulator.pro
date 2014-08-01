#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T09:28:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BPDL_Simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotwindow.cpp \
    qcustomplot.cpp \
    eventclass.cpp \
    filestreaming.cpp \
    randomdice.cpp \
    traitclass.cpp \
    traiteventmanager.cpp \
    graphclass.cpp

HEADERS  += mainwindow.h \
    plotwindow.h \
    qcustomplot.h \
    eventclass.h \
    filestreaming.h \
    randomdice.h \
    traitclass.h \
    traiteventmanager.h \
    graphclass.h

FORMS    += mainwindow.ui \
    plotwindow.ui

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

OTHER_FILES += \
    ../build-BPDL_Simulator-Desktop_Qt_5_2_1_MinGW_32bit-Debug/RightInstance1
