include("../../src/common.pri")

SOURCES += main.cpp

INCLUDEPATH += $${BULLET_INCLUDE_PATH}
LIBS += $${BULLET_LIBS_PATH}

unix {
    #CONFIG += link_pkgconfig
    #PKGCONFIG += bullet
}
