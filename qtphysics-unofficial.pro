load(configure)
qtCompileTest(bullet)

TEMPLATE = subdirs
CONFIG += ordered

if(config_bullet){
}
else{
    message("Bullet not found")
}
qtHaveModule(3dcore){
    SUBDIRS += \
        src \
        examples
}else{
    message("physics needs qt3d")
}
