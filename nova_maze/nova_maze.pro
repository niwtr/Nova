#-------------------------------------------------
#
# Project created by QtCreator 2015-12-26T14:21:54
#
#-------------------------------------------------

QT       += core gui
CONFIG   += C++11
CONFIG   += C++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMazeProject
TEMPLATE = app


SOURCES += main.cpp\
    path_maze.cpp \
    maze_widget.cpp

HEADERS  += \
    astar.hpp \
    path_maze.h \
    maze_widget.h

RESOURCES +=
RC_FILE = s.rc
