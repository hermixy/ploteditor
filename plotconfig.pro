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

INCLUDEPATH += 3rdparty \
    src

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settings.cpp \
    src/xlsx_sql.cpp \
    src/settings_data.cpp \
    src/utils.cpp \
    src/progressbar.cpp \
    src/pch.cpp \
    src/plotviewer/ploteditdialog.cpp \
    src/plotviewer/plotitem.cpp \
    src/plotviewer/plotviewer.cpp \
    src/plotviewer/plot_viewer_item.cpp \
    src/plotviewer/plot_viewer_model.cpp \
    src/plot_row_data.cpp \
    src/json_config.cpp

HEADERS += \
    src/mainwindow.h \
    src/settings.h \
    src/pch.h \
    src/xlsx_sql.h \
    src/settings_data.h \
    src/utils.h \
    src/progressbar.h \
    src/plotviewer/ploteditdialog.h \
    src/plotviewer/plotitem.h \
    src/plotviewer/plotviewer.h \
    src/plotviewer/plot_viewer_item.h \
    src/plotviewer/plot_viewer_model.h \
    src/plot_row_data.h \
    src/json_config.h

FORMS += \
    src/mainwindow.ui \
    src/settings.ui \
    src/progressbar.ui \
    src/plotviewer/ploteditdialog.ui \
    src/plotviewer/plotviewer.ui

DISTFILES += \
    notes.md

RESOURCES += \
    jsonfiles.qrc
