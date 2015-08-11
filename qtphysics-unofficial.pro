load(configure)
qtCompileTest(bullet)

TEMPLATE = subdirs
CONFIG += ordered

qtHaveModule(3dcore){
    SUBDIRS += \
        src \
        examples
    if(config_bullet){
        SUBDIRS += \
            plugins
    }
    else{
        message("Bullet not found")
    }
}else{
    message("physics needs Qt3d 2.0")

}

