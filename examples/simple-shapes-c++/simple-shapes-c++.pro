android|ios|tvos|winrt {
    warning( "This example is not supported for android, ios, tvos, or winrt." )
}


QT += 3dcore 3drender 3dinput 3dextras qml
QT += widgets

SOURCES += main.cpp

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtPhysicsUnofficial


!android{
    LIBS += -L/home/chili/Downloads/bullet3-2.83.5/build-linux/install/lib
}

LIBS += -lLinearMath -lBulletDynamics -lBulletCollision

#HEADERS += \
#    physicssetter.h

LIBS += -lQtPhysicsUnofficial
LIBS += -L../../src/lib
