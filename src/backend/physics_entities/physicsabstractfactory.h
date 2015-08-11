#ifndef PHYSICSABSTRACTFACTORY_H
#define PHYSICSABSTRACTFACTORY_H
#include "backend_global.h"
#include "physicsabstractdynamicsworld.h"
#include "physicsabstractrigidbody.h"
#include <QObject>

namespace Physics {


class BACKENDSHARED_EXPORT PhysicsAbstractFactory : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsAbstractFactory(QObject *parent = 0);

    virtual PhysicsAbstractRigidBody* create_rigid_body()=0;
    virtual PhysicsAbstractDynamicsWorld* create_dynamics_world()=0;

signals:

public slots:
};

}

#endif // PHYSICSABSTRACTFACTORY_H
