#include "physics-qml_plugin.h"

#include <physicsbodyinfo.h>
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
     if (library.load())
     qDebug() << "library loaded";

    Q_ASSERT(uri == QLatin1String("QtPhysics.unofficial"));
    //qmlRegisterExtendedType<Physics::PhysicsBodyInfo,Physics::PhysicsQuickBodyInfo>(uri, 1, 0, "PhysicsBodyInfo");

    qmlRegisterType<Physics::PhysicsBodyInfo>(uri, 1, 0, "PhysicsBodyInfo");

}
