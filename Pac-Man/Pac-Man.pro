QT += qml quick quickcontrols2

CONFIG += c++11

SOURCES += main.cpp \
    actor.cpp \
    testactor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    actor.h \
    testactor.h
