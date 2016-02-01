#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T15:01:48
#
#-------------------------------------------------

QT       += core gui 3dcore 3drender

TARGET = bullet
TEMPLATE = lib
CONFIG += plugin

include("../../common.pri")
include("dependencies.pri")

DESTDIR = $$[QT_INSTALL_PLUGINS]/physicsfactories

SOURCES += \
    bulletfactory.cpp \
    #bodies/compoundshape.cpp \
    bodies/motionstate.cpp \
    worlds/dynamicsworld.cpp \
    bodies/abstractrigidbody.cpp \
    bodies/rigidboxbody.cpp \
    bodies/rigidstaticplanebody.cpp \
    bodies/rigidconvexhullbody.cpp \
    bodies/rigidspherebody.cpp

HEADERS += \
    bulletfactory.h \
    #bodies/compoundshape.h \
    bodies/motionstate.h \
    worlds/dynamicsworld.h \
    bodies/abstractrigidbody.h \
    bodies/rigidboxbody.h \
    bodies/rigidconvexhullbody.h \
    bodies/rigidspherebody.h \
    bodies/rigidstaticplanebody.h
DISTFILES += bullet.json \


LIBS += -lQtPhysicsUnofficialBackend

INCLUDEPATH += $${BULLET_INCLUDE_PATH}
LIBS += $${BULLET_LIBS_PATH}
