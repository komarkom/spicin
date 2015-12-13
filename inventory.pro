#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T12:21:02
#
#-------------------------------------------------

QT       += core gui widgets designer sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inventory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataprovider.cpp \
    merror.cpp

HEADERS  += mainwindow.h \
    dataprovider.h \
    MObjectInv.h \
    merror.h

FORMS    += mainwindow.ui
