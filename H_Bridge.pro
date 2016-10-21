#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T17:11:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = H_Bridge
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    searchbox.cpp \
    serialmonitor.cpp \
    themepicker.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    highlighter.h \
    searchbox.h \
    serialmonitor.h \
    themepicker.h

FORMS    += mainwindow.ui \
    searchbox.ui \
    serialmonitor.ui \
    themepicker.ui

RESOURCES += \
    recources.qrc

QMAKE_CXXFLAGS += -pthread
