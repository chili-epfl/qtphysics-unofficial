#ifndef PHYSICSFACTORYINTERFACE_H
#define PHYSICSFACTORYINTERFACE_H
#include "backend_global.h"
#include "physicsabstractdynamicsworld.h"
#include "physicsabstractrigidbody.h"
#include <QObject>

namespace Physics {


class BACKENDSHARED_EXPORT PhysicsFactoryInterface
{
public:
    virtual PhysicsAbstractRigidBody* create_rigid_body(QVariantMap geometric_info)=0;
    virtual PhysicsAbstractDynamicsWorld* create_dynamics_world()=0;
};
}

#define PhysicsFactoryInterface_iid "org.qt-project.Qt.Physics.Unofficial.PhysicsFactoryInterface"
Q_DECLARE_INTERFACE(Physics::PhysicsFactoryInterface, PhysicsFactoryInterface_iid)


#endif // PHYSICSFACTORYINTERFACE_H
