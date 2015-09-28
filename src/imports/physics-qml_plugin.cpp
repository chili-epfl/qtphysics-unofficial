#include "physics-qml_plugin.h"

#include <physicsbodyinfo.h>
#include <physicsworldinfo.h>
#include <physicsaspect.h>
#include <QLibrary>
#include <qqml.h>

void Qml_PhysicsPlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents
    /*This is here just to load the backend library*/
     QLibrary library("QtPhysicsUnofficialBackend");
     if (!library.load())
         qDebug() << library.errorString();

    Q_ASSERT(uri == QLatin1String("QtPhysics.unofficial"));

    qmlRegisterType<Physics::PhysicsBodyInfo>(uri, 1, 0, "PhysicsBodyInfo");
    qmlRegisterType<Physics::PhysicsWorldInfo>(uri, 1, 0, "PhysicsWorldInfo");
    qmlRegisterUncreatableType<Physics::PhysicsCollisionEvent>(uri, 1, 0, "PhysicsCollisionEvent", QStringLiteral("Events cannot be created"));
}
