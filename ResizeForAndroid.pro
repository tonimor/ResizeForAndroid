#-------------------------------------------------
#
# Project created by QtCreator 2015-09-22T13:26:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ResizeForAndroid
TEMPLATE = app

SOURCES += main.cpp\
    QWaitcursor.cpp \
    QResizeApp.cpp \
    QResizeDialog.cpp

HEADERS  += \
    QWaitcursor.h \
    QResizeApp.h \
    QResizeDialog.h

FORMS    += \
    ResizeDialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

win32:RC_ICONS += resize.ico
