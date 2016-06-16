include("../../plugins/bullet/dependencies.pri")

SOURCES += main.cpp

INCLUDEPATH += $${BULLET_INCLUDE_PATH}
LIBS += $${BULLET_LIBS_PATH}

message("Bullet Include:"$${INCLUDEPATH})
message("Bullet Include:"$${LIBS})


