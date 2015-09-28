#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T10:08:11
#
#-------------------------------------------------

include("../common.pri")

QT+= 3dcore 3drenderer 3dquick

CONFIG += c++11

TARGET = QtPhysicsUnofficialFrontend

TEMPLATE = lib

DEFINES += FRONTEND_LIBRARY

DESTDIR = test

SOURCES += \
    physicsbodyinfo.cpp \
    physicsworldinfo.cpp \
    physicscollisionevent.cpp

HEADERS +=\
        frontend_global.h \
        physicsbodyinfo.h \
    physicsworldinfo.h \
    physicscollisionevent.h

headersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME/frontend
headersDataFiles.files = $$PWD/*.h

INSTALLS += headersDataFiles

#libraryFiles.path = $$[QT_INSTALL_LIBS]
#Debug:libraryFiles.files = $$OUT_PWD/debug/*.a $$OUT_PWD/debug/*.prl $$OUT_PWD/debug/*.so
#Release:libraryFiles.files = $$OUT_PWD/release/*.a $$OUT_PWD/release/*.prl $$OUT_PWD/release/*.so
#INSTALLS += libraryFiles

target.path = $$[QT_INSTALL_LIBS]
INSTALLS +=target
