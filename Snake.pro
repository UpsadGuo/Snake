#-------------------------------------------------
#
# Project created by QtCreator 2017-09-03T11:17:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    food.cpp \
    gamecontroller.cpp \
    snake.cpp \
    wall.cpp

HEADERS  += mainwindow.h \
    food.h \
    constants.h \
    gamecontroller.h \
    snake.h \
    wall.h

RESOURCES += \
    icon.qrc
