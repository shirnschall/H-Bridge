#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T17:11:40
#
#-------------------------------------------------

QT       += core gui\
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = H_Bridge
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    searchbox.cpp \
    themepicker.cpp \
    compileroutput.cpp \
    compilerissues.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    highlighter.h \
    searchbox.h \
    themepicker.h \
    compileroutput.h \
    compilerissues.h

FORMS    += mainwindow.ui \
    searchbox.ui \
    themepicker.ui \
    compileroutput.ui \
    compilerissues.ui

RESOURCES += \
    recources.qrc

QMAKE_CXXFLAGS += -pthread
