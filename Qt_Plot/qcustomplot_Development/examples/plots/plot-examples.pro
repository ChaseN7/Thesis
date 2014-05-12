#
#  QCustomPlot Plot Examples
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plot-examples
TEMPLATE = app

SOURCES += main.cpp\
    eventclass.cpp \
    randomdice.cpp \
    traitclass.cpp \
    traiteventmanager.cpp \
    filestreaming.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    eventclass.h \
    randomdice.h \
    traitclass.h \
    traiteventmanager.h \
    filestreaming.h \
    qcustomplot.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    ../build-plot-examples-Desktop_Qt_5_2_1_MinGW_32bit-Debug/SecondTest.txt \
    ../build-plot-examples-Desktop_Qt_5_2_1_MinGW_32bit-Debug/FirstTest.txt
