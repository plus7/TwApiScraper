# -------------------------------------------------
# Project created by QtCreator 2010-02-19T05:37:28
# -------------------------------------------------
QT += network \
    xml \
    gui

# QT -= gui
TARGET = testproj
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    petrel.cpp \
    ../petrel_impl.cpp \
    testapp.cpp
HEADERS += petrel.h \
    ../petrel_types.h \
    testapp.h
