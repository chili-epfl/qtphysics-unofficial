#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T15:01:48
#
#-------------------------------------------------

QT       += core gui 3dcore 3drender

TARGET = bullet
TEMPLATE = lib
CONFIG += plugin
CONFIG -= android_install

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

INCLUDEPATH += $$PWD/../../src/backend
INCLUDEPATH += $$PWD/../../src/
INCLUDEPATH += $$PWD

DISTFILES += bullet.json \

INCLUDEPATH += $${BULLET_INCLUDE_PATH}
LIBS += $${BULLET_LIBS_PATH}

LIBS += -lQtPhysicsUnofficial
LIBS += -L../../src/lib
