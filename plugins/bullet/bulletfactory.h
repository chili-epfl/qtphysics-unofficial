#ifndef BulletFactory_H
#define BulletFactory_H

#include <QGenericPlugin>
#include <physics_entities/physicsfactoryinterface.h>
namespace Physics {

namespace Bullet {

class BulletFactory :public QObject,
        PhysicsFactoryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Physics.Unofficial.PhysicsFactoryInterface" FILE "bullet.json")
    Q_INTERFACES(Physics::PhysicsFactoryInterface)
public:
    BulletFactory(QObject *parent = 0);
    PhysicsAbstractRigidBody* create_rigid_body(QVariantMap geometric_info);
    PhysicsAbstractDynamicsWorld* create_dynamics_world();
};


}
}
#endif // BulletFactory_H
