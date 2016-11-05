TEMPLATE = app

QT += 3dcore 3drender 3dinput 3dquick qml quick
CONFIG += c++11
#CONFIG -= android_install

SOURCES += main.cpp
#    physicssetter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)


android{
    LIBS += -L/home/chili/bullet3-2.83.5/build_android/install/lib/
}

!android{
    LIBS += -L/home/chili/Downloads/bullet3-2.83.5/build-linux/install/lib
}

LIBS += -lLinearMath -lBulletDynamics -lBulletCollision

#HEADERS += \
#    physicssetter.h

LIBS += -lQtPhysicsUnofficial
LIBS += -L../../src/lib

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        /home/chili/QTProjects/qtphysics-unofficial/examples/aspect-test/../../../../bullet3-2.83.5/build_android/install/lib/libLinearMath.so \
        /home/chili/QTProjects/qtphysics-unofficial/examples/aspect-test/../../../../bullet3-2.83.5/build_android/install/lib/libBulletDynamics.so \
        /home/chili/QTProjects/qtphysics-unofficial/examples/aspect-test/../../../../bullet3-2.83.5/build_android/install/lib/libBulletCollision.so \
        /home/chili/QTProjects/qtphysics-unofficial/examples/aspect-test/../../../../bullet3-2.83.5/build_android/install/lib/libBulletSoftBody.so \
        $$PWD/../../../../Qt/5.6/android_armv7/plugins/physicsfactories/libbullet.so
}
