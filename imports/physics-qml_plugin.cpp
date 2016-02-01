#include "physics-qml_plugin.h"

#include <physicsbodyinfo.h>
#include <physicsworldinfo.h>
#include <qqml.h>

void Qml_PhysicsPlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
    Q_ASSERT(uri == QLatin1String("QtPhysics.unofficial"));
    qmlRegisterType<Physics::PhysicsBodyInfo>(uri, 1, 0, "PhysicsBodyInfo");
    qmlRegisterType<Physics::PhysicsWorldInfo>(uri, 1, 0, "PhysicsWorldInfo");
    qmlRegisterUncreatableType<Physics::PhysicsCollisionEvent>(uri, 1, 0, "PhysicsCollisionEvent", QStringLiteral("Events cannot be created"));
}
