#-------------------------------------------------
#
# Project created by QtCreator 2019-06-12T11:10:48
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
LIBS     += C:\Users\Luna\Desktop\Qtworkplace\build-temControl-Desktop_Qt_5_9_6_MinGW_32bit-Debug\AL808_DRV\AL808\debug\AL808.dll
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_AL808
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    ../AL808/AL808.h \
    ../AL808/al808_global.h

FORMS += \
        mainwindow.ui
