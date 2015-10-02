#ifndef PHYSICSABSTRACTSOFTRIGIDDYNAMICSWORLD_H
#define PHYSICSABSTRACTSOFTRIGIDDYNAMICSWORLD_H

#include "physicsabstractdynamicsworld.h"
#include "physicsabstractsoftbody.h"

namespace Physics {


class PhysicsAbstractSoftRigidDynamicsWorld: public PhysicsAbstractDynamicsWorld
{
    Q_OBJECT
public:
    explicit PhysicsAbstractSoftRigidDynamicsWorld();

    virtual WorldType type(){return SOFTRIGIDDYNAMICSWORLD;}

    virtual void addSoftBody(PhysicsAbstractSoftBody* body)=0;
    virtual void removeSoftBody(PhysicsAbstractSoftBody* body)=0;



};

 }
#endif // PHYSICSABSTRACTSOFTRIGIDDYNAMICSWORLD_H
