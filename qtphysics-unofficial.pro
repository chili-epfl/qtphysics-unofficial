load(configure)
qtCompileTest(bullet)

TEMPLATE = subdirs
CONFIG += ordered

qtHaveModule(3dcore){
    SUBDIRS += \
        src \
        examples

}else{
    message("Physics needs Qt3d 2.0")

}

