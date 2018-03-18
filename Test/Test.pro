QT += testlib
QT -= gui

TARGET = main

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
MOC_DIR = moc
OBJECTS_DIR = obj

INCLUDEPATH += $$PWD/../MLElib/include \
            $$PWD/src

SOURCES += \
    src/*.cpp \
    testAll.cpp

QMAKE_CXXFLAGS += -std=c++14

#clang
linux-clang++: QMAKE_CXXFLAGS += -Weverything -Wno-c++98-compat
#gcc
linux-g++: QMAKE_CXXFLAGS += -Wall -Wextra -pedantic-errors
