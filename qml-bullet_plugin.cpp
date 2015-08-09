#include "qml-bullet_plugin.h"
#include "extra/qt3d/physicsaspect.h"

#include <qqml.h>

void Qml_BulletPlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
    qmlRegisterType<Physics::PhysicsAspect>(uri, 1, 0, "PhysicsAspect");

}


