#-------------------------------------------------
#
# Project created by QtCreator 2014-10-10T16:47:38
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SiteLottery
TEMPLATE = app


SOURCES += main.cpp\
        sitelotterymain.cpp \
    InitTotalNumDialog.cpp \
    InitWeWantNumDialog.cpp

HEADERS  += sitelotterymain.h \
    config.h \
    InitTotalNumDialog.h \
    InitWeWantNumDialog.h

FORMS    += sitelotterymain.ui \
    inittotalnumdialog.ui \
    initwewantnumdialog.ui

RESOURCES += \
    images.qrc

RC_FILE = \
    sitelottery.rc
