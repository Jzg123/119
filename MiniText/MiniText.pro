#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T06:53:35
#
#-------------------------------------------------

QT       += core gui

qtHaveModule(printsupport): QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniText
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    replacedialog.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    replacedialog.h

RESOURCES += \
    res.qrc
RC_FILE = myapp.rc
