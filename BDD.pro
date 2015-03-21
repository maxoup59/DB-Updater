#-------------------------------------------------
#
# Project created by QtCreator 2015-03-16T20:51:34
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDD
TEMPLATE = app

test.sources = "test.dev.db"
test.path = .
DEPLOYMENT += test

SOURCES += main.cpp\
        mainwindow.cpp \
    db.cpp \
    threadintegration.cpp

HEADERS  += mainwindow.h \
    db.h \
    threadintegration.h

FORMS    += mainwindow.ui

DISTFILES += \
    test.dev.db
