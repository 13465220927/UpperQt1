#-------------------------------------------------
#
# Project created by QtCreator 2015-01-05T19:37:43
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UpperQt1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    buttonthread.cpp \
    qlinkqdbc.cpp \
    logindia.cpp

HEADERS  += mainwindow.h \
    buttonthread.h \
    qlinkqdbc.h \
    logindia.h

FORMS    += mainwindow.ui \
    logindia.ui

OTHER_FILES += \
    readme.txt

RESOURCES += \
    new.qrc
