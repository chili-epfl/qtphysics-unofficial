TEMPLATE = lib
TARGET = physics

include("dependencies.pri")

QT += qml quick
QT += 3dcore 3drender 3dquick

CONFIG += qt plugin c++11
CONFIG -= android_install

uri = QtPhysics.unofficial

LIBS += -lQtPhysicsUnofficialFrontend -lQtPhysicsUnofficialBackend

# Input
SOURCES += \
    physics-qml_plugin.cpp

HEADERS += \
    physics-qml_plugin.h

DISTFILES = qmldir

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

