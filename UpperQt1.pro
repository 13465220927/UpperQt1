#-------------------------------------------------
#
# Project created by QtCreator 2015-01-05T19:37:43
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UpperQt1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    buttonthread.cpp

HEADERS  += mainwindow.h \
    buttonthread.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    readme.txt
