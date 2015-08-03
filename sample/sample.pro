TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


android {
    target.path = /libs/armeabi-v7a
    export(target.path)
    INSTALLS += target
    export(INSTALLS)

    #In order to debug custum plugin, we need to copy the library in the build dir so that gdb canm load the symbols
    #http://visualgdb.com/gdbreference/commands/set_solib-search-path (I cannot set it in QTC, it is overwritter...)
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../../android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libLinearMath.so \
        $$PWD/../../../android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libBulletCollision.so \
        $$PWD/../../../android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libBulletDynamics.so \
        $$PWD/../../../android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libBulletSoftBody.so \

}

# Default rules for deployment.
include(deployment.pri)



