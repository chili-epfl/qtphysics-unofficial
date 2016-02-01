load(configure)
qtCompileTest(bullet)

TEMPLATE = subdirs
CONFIG += ordered

BULLET_LIBS_PATH += -lLinearMath -lBulletDynamics -lBulletCollision -lBulletSoftBody


qtHaveModule(3dcore){
    SUBDIRS += \
        src \
        imports

if(config_bullet){
    SUBDIRS += \
         plugins/bullet
}
else{
     message("Bullet not found")
}
     SUBDIRS += examples
}else{
    message("Physics needs Qt3d 2.0")
}

