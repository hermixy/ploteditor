#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T01:12:41
#
#-------------------------------------------------

QT += core gui

include(3rdparty/QtXlsxWriter/src/xlsx/qtxlsx.pri)

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ploteditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settings.cpp \
    src/xlsx_sql.cpp \
    src/settings_data.cpp

HEADERS += \
    src/mainwindow.h \
    src/settings.h \
    src/pch.h \
    src/xlsx_sql.h \
    src/settings_data.h

FORMS += \
    src/mainwindow.ui \
    src/settings.ui
