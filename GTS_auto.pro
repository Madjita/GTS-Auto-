#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T14:52:50
#
#-------------------------------------------------

QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GTS_auto
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
        mainwindow.cpp \
    n9000a.cpp \
    gts.cpp \
    windowachh.cpp \
    windowdevice.cpp \
    toolbox.cpp \
    callout.cpp \
    view.cpp \
    window10khz.cpp \
    windowattmax.cpp \
    windowcollateral.cpp \
    windowspectr.cpp \
    windownes.cpp \
    dialogseiting.cpp \
    screenn9000.cpp \
    windowfinddevice.cpp

HEADERS += \
        mainwindow.h \
    n9000a.h \
    gts.h \
    windowachh.h \
    windowdevice.h \
    toolbox.h \
    callout.h \
    view.h \
    window10khz.h \
    windowattmax.h \
    windowcollateral.h \
    windowspectr.h \
    windownes.h \
    dialogseiting.h \
    screenn9000.h \
    windowfinddevice.h

FORMS += \
        mainwindow.ui \
    windowachh.ui \
    windowdevice.ui \
    window10khz.ui \
    windowattmax.ui \
    windowcollateral.ui \
    windowspectr.ui \
    windownes.ui \
    dialogseiting.ui \
    windowfinddevice.ui

target.path = $$[QT_INSTALL_EXAMPLES]/charts/callout

LIBS += -L$$PWD/ -lMiVISA32

LIBS += -L$$PWD/ -lAutoWorkplace1


RESOURCES += \
    resources.qrc
