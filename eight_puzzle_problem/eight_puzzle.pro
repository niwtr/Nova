#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T15:20:13
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eight_puzzle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    numblock.cpp

HEADERS  += mainwindow.h \
    def.h \
    common_animation.h \
    pushbtn.h \
    path_pacman.h \
    astar.hpp \
    Path8.h \
    numblock.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    picture.qrc
