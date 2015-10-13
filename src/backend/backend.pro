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
    backendtypes/physicstransform.cpp \
    jobs/debugjob.cpp \
    #jobs/insertphysicstransformjob.cpp \
    physicsaspect.cpp \
    physicsmanager.cpp \
    backendtypes/physicsworldinfobackendnode.cpp \
    physics_entities/physicsabstractrigidbody.cpp \
    physics_entities/physicsabstractdynamicsworld.cpp \
    jobs/simulatestepjob.cpp \
    jobs/updatephysicsentitiesjob.cpp \
    jobs/updatetransformsjob.cpp \
    backendtypes/physicsgeometryrenderer.cpp \
    backendtypes/physicsgeometry.cpp \
    backendtypes/physicsattribute.cpp \
    backendtypes/physicsbuffer.cpp \
    jobs/notifycollisionsjob.cpp \
    backendtypes/physicssoftbodyinfobackendnode.cpp \
    physics_entities/physicsabstractsoftbody.cpp \
    physics_entities/physicsabstractsoftrigiddynamicsworld.cpp

HEADERS +=\
        backend_global.h \
    backendtypes/physicsbodyinfobackendnode.h \
    backendtypes/physicsentity.h \
    backendtypes/physicstransform.h \
    jobs/debugjob.h \
    #jobs/insertphysicstransformjob.h \
    physicsaspect.h \
    physicsmanager.h \
    physics_entities/physicsabstractrigidbody.h \
    physics_entities/physicsabstractdynamicsworld.h \
    backendtypes/physicsworldinfobackendnode.h \
    jobs/simulatestepjob.h \
    jobs/updatephysicsentitiesjob.h \
    jobs/updatetransformsjob.h \
    physics_entities/physicsfactoryinterface.h \
    backendtypes/physicsgeometryrenderer.h \
    backendtypes/physicsgeometry.h \
    backendtypes/physicsattribute.h \
    backendtypes/physicsbuffer.h \
    jobs/notifycollisionsjob.h \
    backendtypes/physicssoftbodyinfobackendnode.h \
    physics_entities/physicsabstractsoftbody.h \
    physics_entities/physicsabstractsoftrigiddynamicsworld.h \
    physicscollition.h


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
