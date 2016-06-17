TARGET = QtPhysicsUnofficial
TEMPLATE = lib
PROJECT_NAME=QtPhysicsUnofficial

QT+= 3dcore 3dquick 3drender

DESTDIR+= ./lib

CONFIG += c++11
CONFIG -= android_install

DEFINES += QTPHYSICSUNOFFICIAL_LIBRARY

HEADERS += \
    qtphysicsunofficial_global.h

include(frontend/frontend.pri)
include(backend/backend.pri)

INCLUDEPATH += $$PWD $$[QT_INSTALL_HEADERS]/../../Src/qt3d/include/Qt3DCore/5.7.0/ $$[QT_INSTALL_HEADERS]/../../Src/qtbase/include/QtCore/5.7.0/QtCore/
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../../Src/qt3d/include/Qt3DCore/5.7.0/Qt3DCore
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../../Src/qt3d/include/Qt3DRender/5.7.0/ $$[QT_INSTALL_HEADERS]/../../Src/qtbase/include/Qt3DRender/5.7.0/Qt3DRender/
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../../Src/qt3d/include/Qt3DRender/5.7.0/Qt3DRender

headersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME
headersDataFiles.files = $$PWD/*.h


INSTALLS += headersDataFiles

target.path = $$[QT_INSTALL_LIBS]
INSTALLS +=target
