#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T01:12:41
#
#-------------------------------------------------

QT += core gui

INCLUDEPATH = 3rdlibs/libxl/include_cpp
LIBS += 3rdlibs/libxl/lib/libxl.lib

#QMAKE_POST_LINK += $$quote(cmd /c copy /y .\3rdlibs\libxl\bin\libxl.dll .)

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plotconfig
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
