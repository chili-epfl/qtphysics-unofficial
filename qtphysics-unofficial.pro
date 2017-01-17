load(configure)
qtCompileTest(bullet)

TEMPLATE = subdirs
CONFIG += ordered
CONFIG -= android_install

qtHaveModule(3dcore){
    SUBDIRS += \
        src \
        imports

if(config_bullet){
    message("Bullet found")
    SUBDIRS += \
         plugins/bullet
}
else{
     message("Bullet not found")
}
     #SUBDIRS += examples
}else{
    message("Physics needs Qt3d 2.0")
}
 #Add step make install INSTALL_ROOT=$BUILD_TARGET
