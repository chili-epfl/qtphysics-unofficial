android{
    BULLET_INCLUDE_PATH +=  /home/chili/Downloads/bullet3-2.83.5/build-android/install/include/
    BULLET_INCLUDE_PATH +=  /home/chili/Downloads/bullet3-2.83.5/build-android/install/include/bullet/
    BULLET_LIBS_PATH += -L/home/chili/Downloads/bullet3-2.83.5/build-android/install/lib/
}

!android{
    BULLET_INCLUDE_PATH +=  /home/chili/Downloads/bullet3-2.83.5/build-linux/install/include/
    BULLET_INCLUDE_PATH += /home/chili/Downloads/bullet3-2.83.5/build-linux/install/include/bullet
    BULLET_LIBS_PATH += -L/home/chili/Downloads/bullet3-2.83.5/build-linux/install/lib
}

BULLET_LIBS_PATH += -lLinearMath -lBulletDynamics -lBulletCollision

