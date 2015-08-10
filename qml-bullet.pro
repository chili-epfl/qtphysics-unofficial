TEMPLATE = lib
TARGET = qml-Bullet

QT += qml quick

QT += 3dcore 3drenderer

CONFIG += qt plugin c++11
CONFIG -= android_install


TARGET = $$qtLibraryTarget($$TARGET)
uri = ch.epfl.bulletqml

# Input
SOURCES += \
    qml-bullet_plugin.cpp \
    #world.cpp \
    #simulationthread.cpp \
    #rigidbody.cpp \
    #heightfield2d.cpp \
    #abstractcollitionshape.cpp \
    #sphereshape.cpp \
    #boxshape.cpp \
    extra/qt3d/physicsmanager.cpp \
    extra/qt3d/physicsaspect.cpp \
    extra/qt3d/physicsentity.cpp \
    extra/qt3d/physicsbodyinfo.cpp \
    extra/qt3d/jobs/debugjob.cpp

HEADERS += \
    qml-bullet_plugin.h \
    #world.h \
    #simulationthread.h \
    #rigidbody.h \
    #heightfield2d.h \
    #abstractcollitionshape.h \
    #sphereshape.h \
    #boxshape.h \
    extra/qt3d/physicsmanager.h \
    extra/qt3d/physicsaspect.h \
    extra/qt3d/physicsentity.h \
    extra/qt3d/physicsbodyinfo.h \
    extra/qt3d/jobs/debugjob.h

DISTFILES = qmldir

#LIBS += -lLinearMath -lBulletDynamics -lBulletCollision

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir


android{
    INCLUDEPATH +=  /home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include/
    INCLUDEPATH +=  /home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include/bullet
    LIBS += -L/home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib
}

!android{
    INCLUDEPATH +=  /home/chili/Downloads/bullet3-2.83.5/build-linux/install/include/
    INCLUDEPATH += /home/chili/Downloads/bullet3-2.83.5/build-linux/install/include/bullet
    LIBS += -L/home/chili/Downloads/bullet3-2.83.5/build-linux/install/lib
}
