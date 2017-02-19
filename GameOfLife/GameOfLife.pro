#-------------------------------------------------
#
# Project created by QtCreator 2017-02-11T18:14:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    map.cpp \
    game.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    map.h \
    game.h \
    settings.h

FORMS +=
