#ifndef BulletFactory_H
#define BulletFactory_H

#include <QGenericPlugin>
#include <physics_entities/physicsabstractfactory.h>
namespace Physics {

namespace Bullet {

class BulletFactory : PhysicsAbstractFactory
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Physics.Unofficial.PhysicsAbstractFactory" FILE "bullet.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PhysicsAbstractFactory)
public:
    BulletFactory(QObject *parent = 0);
    PhysicsAbstractRigidBody* create_rigid_body();
    PhysicsAbstractDynamicsWorld* create_dynamics_world();
};


}
}
#endif // BulletFactory_H
