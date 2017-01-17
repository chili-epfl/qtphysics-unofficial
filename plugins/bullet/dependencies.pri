
android{
    BULLET_INCLUDE_PATH +=  /home/chili/bullet3-2.83.5/build_android/install/include/
    BULLET_INCLUDE_PATH +=  /home/chili/bullet3-2.83.5/build_android/install/include/bullet/
    BULLET_LIBS_PATH += -L/home/chili/bullet3-2.83.5/build_android/install/lib/
}

!android{
    BULLET_INCLUDE_PATH +=  /home/chili/bullet3-2.83.5/build_linux/install/include/
    BULLET_INCLUDE_PATH += /home/chili/bullet3-2.83.5/build_linux/install/include/bullet
    BULLET_LIBS_PATH += -L/home/chili/bullet3-2.83.5/build_linux/install/lib
}

BULLET_LIBS_PATH += -lLinearMath -lBulletDynamics -lBulletCollision
