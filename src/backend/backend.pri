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

backend1HeadersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME/backend
backend1HeadersDataFiles.files = $$PWD/*.h
backend2HeadersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME/backend/jobs
backend2HeadersDataFiles.files += $$PWD/jobs/*.h
backend3HeadersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME/backend/backendtypes
backend3HeadersDataFiles.files += $$PWD/backendtypes/*.h
backend4HeadersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME/backend/physics_entities
backend4HeadersDataFiles.files += $$PWD/physics_entities/*.h
INSTALLS += backend1HeadersDataFiles backend2HeadersDataFiles backend3HeadersDataFiles backend4HeadersDataFiles

#libraryFiles.path = $$[QT_INSTALL_LIBS]
#Debug:libraryFiles.files = $$OUT_PWD/debug/*.so $$OUT_PWD/debug/*.prl $$OUT_PWD/debug/*.so
#Release:libraryFiles.files = $$OUT_PWD/release/*.a $$OUT_PWD/release/*.prl
#INSTALLS += libraryFiles
#backendTarget.path = $$[QT_INSTALL_LIBS]
#INSTALLS +=backendTarget
