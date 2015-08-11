#include "bulletfactory.h"

namespace Physics {

namespace Bullet {
BulletFactory::BulletFactory(QObject *parent) :
    PhysicsAbstractFactory(parent)
{
}

PhysicsAbstractRigidBody* BulletFactory::create_rigid_body(){


}
PhysicsAbstractDynamicsWorld* BulletFactory::create_dynamics_world(){


}

}

}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bullet, BulletFactory)
#endif // QT_VERSION < 0x050000
