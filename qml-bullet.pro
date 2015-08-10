TEMPLATE = lib
TARGET = qml-Bullet

QT += qml quick 3dcore 3drenderer
CONFIG += qt plugin c++11
CONFIG -= android_install


TARGET = $$qtLibraryTarget($$TARGET)
uri = ch.epfl.bulletqml

# Input
SOURCES += \
    qml-bullet_plugin.cpp \
    src/world.cpp \
    src/simulationthread.cpp \
    src/CollitionShapes/heightfield2d.cpp \
    src/CollitionShapes/sphereshape.cpp \
    src/CollitionShapes/boxshape.cpp \
    src/CollitionShapes/convexhullshape.cpp \
    src/CollitionShapes/motionstate.cpp \
    src/CollitionShapes/compoundshape.cpp \
    src/CollitionShapes/abstractbody.cpp \
    src/extra/qt3dbody.cpp

HEADERS += \
    qml-bullet_plugin.h \
    src/world.h \
    src/simulationthread.h \
    src/CollitionShapes/heightfield2d.h \
    src/CollitionShapes/sphereshape.h \
    src/CollitionShapes/boxshape.h \
    src/CollitionShapes/convexhullshape.h \
    src/CollitionShapes/motionstate.h \
    src/CollitionShapes/compoundshape.h \
    src/CollitionShapes/abstractbody.h \
    src/extra/qt3dbody.h

DISTFILES = qmldir

LIBS += -lLinearMath -lBulletDynamics -lBulletCollision

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
