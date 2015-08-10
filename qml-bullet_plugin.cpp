#include "qml-bullet_plugin.h"

/*#include "src/world.h"
#include "src/CollitionShapes/boxshape.h"
#include "src/CollitionShapes/heightfield2d.h"
#include "src/CollitionShapes/sphereshape.h"
#include "src/CollitionShapes/heightfield2d.h"*/
#include "extra/qt3d/physicsaspect.h"

#include <qqml.h>

void Qml_BulletPlugin::registerTypes(const char *uri)
{
    // @uri com.mycompany.qmlcomponents

    Q_ASSERT(uri == QLatin1String("ch.epfl.bulletqml"));
    /*
  qmlRegisterType<Bullet::World>(uri, 1, 0, "World");
  qmlRegisterType<Bullet::BoxShape>(uri, 1, 0, "Box");
  qmlRegisterType<Bullet::SphereShape>(uri, 1, 0, "Sphere");
  qmlRegisterType<Bullet::HeightField2D>(uri, 1, 0, "HeightField2D");*/
    qmlRegisterType<Physics::PhysicsAspect>(uri, 1, 0, "PhysicsAspect");

}


