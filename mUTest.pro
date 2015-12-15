#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T00:44:05
#
#-------------------------------------------------

QT       += widgets sql testlib printsupport

TARGET = tst_mutest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_mutest.cpp \
    dataprovider.cpp \
    merror.cpp \
    utils.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

FORMS +=

HEADERS += \
    dataprovider.h \
    merror.h \
    MObjectInv.h \
    utils.h

DISTFILES += \
    mUTest.pro.user
