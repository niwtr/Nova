#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T15:20:13
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    def.h \
    common_animation.h \
    pushbtn.h \
    path_pacman.h \
    astar.hpp \
    Path8.h

FORMS    += mainwindow.ui
