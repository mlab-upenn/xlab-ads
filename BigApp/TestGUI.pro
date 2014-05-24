#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:36:57
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicsview.cpp \
    mygraphicsscene.cpp \
    socketcomm.cpp \
    frame.cpp \
    xmldataparser.cpp

HEADERS  += mainwindow.h \
    mygraphicsview.h \
    mygraphicsscene.h \
    socketcomm.h \
    frame.h \
    xmldataparser.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    panda_AP.jpg

RESOURCES += \
    Resources.qrc
