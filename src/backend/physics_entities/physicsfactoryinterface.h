#ifndef PHYSICSFACTORYINTERFACE_H
#define PHYSICSFACTORYINTERFACE_H
#include "qtphysicsunofficial_global.h"
#include "physicsabstractdynamicsworld.h"
#include "physicsabstractsoftrigiddynamicsworld.h"
#include "physicsabstractrigidbody.h"
#include "physicsabstractsoftbody.h"
#include <QObject>

namespace Physics {


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsFactoryInterface
{
public:
    virtual PhysicsAbstractSoftBody* create_soft_body(QVariantMap geometric_info)=0;
    virtual PhysicsAbstractRigidBody* create_rigid_body(QVariantMap geometric_info)=0;

    virtual PhysicsAbstractDynamicsWorld* create_dynamics_world()=0;
    virtual PhysicsAbstractSoftRigidDynamicsWorld* create_soft_rigid_dynamics_world()=0;

};
}

#define PhysicsFactoryInterface_iid "org.qt-project.Qt.Physics.Unofficial.PhysicsFactoryInterface"
Q_DECLARE_INTERFACE(Physics::PhysicsFactoryInterface, PhysicsFactoryInterface_iid)

#endif // PHYSICSFACTORYINTERFACE_H
