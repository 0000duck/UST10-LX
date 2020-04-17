#-------------------------------------------------
#
# Project created by QtCreator 2020-04-04T14:19:14
#
#-------------------------------------------------

QT       += core gui opengl
QT += widgets printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ust10lx2
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
QT += network
QT += gui
LIBS += -lopengl32

SOURCES += main.cpp\
        mainwindow.cpp \
    decode.cpp \
    qcustomplot.cpp \
    drawer3d.cpp
HEADERS  += mainwindow.h \
    decode.h \
    qcustomplot.h \
    drawer3d.h
FORMS    += mainwindow.ui
