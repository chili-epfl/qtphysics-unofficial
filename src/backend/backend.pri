#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T09:58:05
#
#-------------------------------------------------

SOURCES += \
    $$PWD/backendtypes/physicsbodyinfobackendnode.cpp \
    $$PWD/backendtypes/physicsentity.cpp \
    $$PWD/backendtypes/physicstransform.cpp \
    $$PWD/jobs/debugjob.cpp \
    #jobs/insertphysicstransformjob.cpp \
    $$PWD/physicsmanager.cpp \
    $$PWD/backendtypes/physicsworldinfobackendnode.cpp \
    $$PWD/physics_entities/physicsabstractrigidbody.cpp \
    $$PWD/physics_entities/physicsabstractdynamicsworld.cpp \
    $$PWD/jobs/simulatestepjob.cpp \
    $$PWD/jobs/updatephysicsentitiesjob.cpp \
    $$PWD/jobs/updatetransformsjob.cpp \
    $$PWD/backendtypes/physicsgeometryrenderer.cpp \
    $$PWD/backendtypes/physicsgeometry.cpp \
    $$PWD/backendtypes/physicsattribute.cpp \
    $$PWD/backendtypes/physicsbuffer.cpp \
    $$PWD/jobs/notifycollisionsjob.cpp
#    $$PWD/backendtypes/physicssoftbodyinfobackendnode.cpp \
#    $$PWD/physics_entities/physicsabstractsoftbody.cpp \
#    $$PWD/physics_entities/physicsabstractsoftrigiddynamicsworld.cpp

HEADERS +=\
    $$PWD/backendtypes/physicsbodyinfobackendnode.h \
    $$PWD/backendtypes/physicsentity.h \
    $$PWD/backendtypes/physicstransform.h \
    $$PWD/jobs/debugjob.h \
    #jobs/insertphysicstransformjob.h \
    $$PWD/physicsmanager.h \
    $$PWD/physics_entities/physicsabstractrigidbody.h \
    $$PWD/physics_entities/physicsabstractdynamicsworld.h \
    $$PWD/backendtypes/physicsworldinfobackendnode.h \
    $$PWD/jobs/simulatestepjob.h \
    $$PWD/jobs/updatephysicsentitiesjob.h \
    $$PWD/jobs/updatetransformsjob.h \
    $$PWD/physics_entities/physicsfactoryinterface.h \
    $$PWD/backendtypes/physicsgeometryrenderer.h \
    $$PWD/backendtypes/physicsgeometry.h \
    $$PWD/backendtypes/physicsattribute.h \
    $$PWD/backendtypes/physicsbuffer.h \
    $$PWD/jobs/notifycollisionsjob.h \
#    $$PWD/backendtypes/physicssoftbodyinfobackendnode.h \
#    $$PWD/physics_entities/physicsabstractsoftbody.h \
#    $$PWD/physics_entities/physicsabstractsoftrigiddynamicsworld.h \
    $$PWD/physicscollision.h

INCLUDEPATH += $$PWD

backendHeadersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME
backendHeadersDataFiles.files = $$PWD/*.h
backendHeadersDataFiles.files += $$PWD/jobs/*.h
backendHeadersDataFiles.files += $$PWD/backendtypes/*.h
INSTALLS += backendHeadersDataFiles

#libraryFiles.path = $$[QT_INSTALL_LIBS]
#Debug:libraryFiles.files = $$OUT_PWD/debug/*.so $$OUT_PWD/debug/*.prl $$OUT_PWD/debug/*.so
#Release:libraryFiles.files = $$OUT_PWD/release/*.a $$OUT_PWD/release/*.prl
#INSTALLS += libraryFiles
#backendTarget.path = $$[QT_INSTALL_LIBS]
#INSTALLS +=backendTarget
