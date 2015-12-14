#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T12:21:02
#
#-------------------------------------------------

QT       += core gui widgets designer sql designer quickwidgets qml quick webkitwidgets webkit printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inventory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataprovider.cpp \
    merror.cpp \
    utils.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    dataprovider.h \
    MObjectInv.h \
    merror.h \
    utils.h \
    qcustomplot.h

FORMS    += mainwindow.ui
