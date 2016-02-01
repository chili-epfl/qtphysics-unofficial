#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T10:08:11
#
#-------------------------------------------------

SOURCES += \
    $$PWD/physicsbodyinfo.cpp \
    $$PWD/physicsworldinfo.cpp \
    $$PWD/physicscollisionevent.cpp \
    $$PWD/physicssoftbodyinfo.cpp \
    $$PWD/physicsaspect.cpp

HEADERS +=\
        $$PWD/physicsbodyinfo.h \
        $$PWD/physicsworldinfo.h \
        $$PWD/physicscollisionevent.h \
        $$PWD/physicssoftbodyinfo.h \
        $$PWD/physicsaspect.h

INCLUDEPATH += $$PWD


frontHeadersDataFiles.path = $$[QT_INSTALL_HEADERS]/$$PROJECT_NAME
frontHeadersDataFiles.files = $$PWD/*.h

INSTALLS += frontHeadersDataFiles

#libraryFiles.path = $$[QT_INSTALL_LIBS]
#Debug:libraryFiles.files = $$OUT_PWD/debug/*.a $$OUT_PWD/debug/*.prl $$OUT_PWD/debug/*.so
#Release:libraryFiles.files = $$OUT_PWD/release/*.a $$OUT_PWD/release/*.prl $$OUT_PWD/release/*.so
#INSTALLS += libraryFiles

#frontendTarget.path = $$[QT_INSTALL_LIBS]
#INSTALLS +=frontendTarget
