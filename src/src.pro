TEMPLATE = subdirs
CONFIG += ordered


SUBDIRS += \
    frontend \
    backend \
    imports  #\

if(config_bullet){
    SUBDIRS += \
         plugins/bullet
}
else{
     message("Bullet not found")
}
		
