#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T01:12:41
#
#-------------------------------------------------

QT += core gui sql

include(3rdparty/QtXlsxWriter/src/xlsx/qtxlsx.pri)

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ploteditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += 3rdparty

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settings.cpp \
    src/xlsx_sql.cpp \
    src/settings_data.cpp \
    src/utils.cpp \
    src/progressbar.cpp \
    src/pch.cpp \
    src/ploteditdialog.cpp \
    src/plotitem.cpp \
    src/plotviewer.cpp \
    src/plot_viewer_item.cpp

HEADERS += \
    src/mainwindow.h \
    src/settings.h \
    src/pch.h \
    src/xlsx_sql.h \
    src/settings_data.h \
    src/utils.h \
    src/progressbar.h \
    src/ploteditdialog.h \
    src/plotitem.h \
    src/plotviewer.h \
    src/plot_viewer_item.h

FORMS += \
    src/mainwindow.ui \
    src/settings.ui \
    src/progressbar.ui \
    src/ploteditdialog.ui \
    src/plotviewer.ui

DISTFILES += \
    notes.md

RESOURCES += \
    jsonfiles.qrc
