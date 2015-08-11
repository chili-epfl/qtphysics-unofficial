PROJECT_NAME=QtPhysicsUnofficial

android{
    BULLET_INCLUDE_PATH +=  /home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include/
    BULLET_INCLUDE_PATH +=  /home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include/bullet
    BULLET_LIBS_PATH += -L/home/chili/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib
}

!android{
    BULLET_INCLUDE_PATH +=  /home/chili/Downloads/bullet3-2.83.5/build-linux/install/include/
    BULLET_INCLUDE_PATH += /home/chili/Downloads/bullet3-2.83.5/build-linux/install/include/bullet
    BULLET_LIBS_PATH += -L/home/chili/Downloads/bullet3-2.83.5/build-linux/install/lib
}

BULLET_LIBS_PATH += -lLinearMath -lBulletDynamics -lBulletCollision -lBulletSoftBody
