#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T09:58:05
#
#-------------------------------------------------

include("../common.pri")
include("dependencies.pri")

TARGET = QtPhysicsUnofficialBackend
TEMPLATE = lib
QT+= 3dcore 3drenderer 3dquick

LIBS += -lQtPhysicsUnofficialFrontend

CONFIG += c++11

DEFINES += BACKEND_LIBRARY

SOURCES += \
    backendtypes/physicsbodyinfobackendnode.cpp \
    backendtypes/physicsentity.cpp \
    backendtypes/physicsmesh.cpp \
    backendtypes/physicstransform.cpp \
    jobs/debugjob.cpp \
    jobs/insertphysicstransformjob.cpp \
    physicsaspect.cpp \
    physicsmanager.cpp
    #physics_entities/physicsabstractrigidbody.cpp \
    #physics_entities/physicsabstractdynamicsworld.cpp \
    #physics_entities/physicsabstractfactory.cpp

HEADERS +=\
        backend_global.h \
    backendtypes/physicsbodyinfobackendnode.h \
    backendtypes/physicsentity.h \
    backendtypes/physicsmesh.h \
    backendtypes/physicstransform.h \
    jobs/debugjob.h \
    jobs/insertphysicstransformjob.h \
    physicsaspect.h \
    physicsmanager.h \
    physics_entities/physicsabstractrigidbody.h \
    physics_entities/physicsabstractdynamicsworld.h \
    physics_entities/physicsabstractfactory.h


headersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME/backend
headersDataFiles.files = $$PWD/*.h
headersDataFiles.files += $$PWD/jobs/*.h
headersDataFiles.files += $$PWD/backendtypes/*.h
INSTALLS += headersDataFiles

#libraryFiles.path = $$[QT_INSTALL_LIBS]
#Debug:libraryFiles.files = $$OUT_PWD/debug/*.so $$OUT_PWD/debug/*.prl $$OUT_PWD/debug/*.so
#Release:libraryFiles.files = $$OUT_PWD/release/*.a $$OUT_PWD/release/*.prl
#INSTALLS += libraryFiles
target.path = $$[QT_INSTALL_LIBS]
INSTALLS +=target
