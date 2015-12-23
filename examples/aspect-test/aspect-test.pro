TEMPLATE = app

QT += 3dcore 3drender 3dinput 3dquick qml quick
CONFIG += c++11

SOURCES += main.cpp \
    physicssetter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


android{
    LIBS += -L/home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib
}

!android{
    LIBS += -L/home/chili/Downloads/bullet3-2.83.5/build-linux/install/lib
}

LIBS += -lLinearMath -lBulletDynamics -lBulletCollision -lBulletSoftBody

HEADERS += \
    physicssetter.h
LIBS += -lQtPhysicsUnofficialFrontend
