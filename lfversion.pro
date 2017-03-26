#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T15:39:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lfversion
TEMPLATE = app


SOURCES += main.cpp\
        maininterface.cpp \
    showwidgetui.cpp \
    myrsa.cpp \
    fileoperation.cpp \
    createcertificationui.cpp \
    encryptionui.cpp \
    createaeskeyui.cpp \
    myaes.cpp \
    decryptionui.cpp \
    digitalsignui.cpp \
    verifyui.cpp

HEADERS  += maininterface.h \
    showwidgetui.h \
    myrsa.h \
    fileoperation.h \
    createcertificationui.h \
    encryptionui.h \
    createaeskeyui.h \
    myaes.h \
    decryptionui.h \
    digitalsignui.h \
    verifyui.h

RESOURCES += \
    icon.qrc

LIBS+=-L/usr/lib/  -lcryptopp


