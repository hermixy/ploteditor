#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T01:12:41
#
#-------------------------------------------------

QT += core gui
#CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plotconfig
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/settings.cpp \
    src/editorconfig.cpp

HEADERS += \
        src/mainwindow.h \
        src/settings.h \
    src/editorconfig.h \
    src/pch.h

FORMS += \
    src/mainwindow.ui \
    src/settings.ui
