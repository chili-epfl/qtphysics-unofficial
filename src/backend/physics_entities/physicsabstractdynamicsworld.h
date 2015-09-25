#ifndef PHYSICSABSTRACTDYNAMICSWORLD_H
#define PHYSICSABSTRACTDYNAMICSWORLD_H
#include "backend_global.h"

#include "physicsabstractrigidbody.h"
#include <QObject>

namespace Physics {

class PhysicsAbstractDynamicsWorld : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsAbstractDynamicsWorld(QObject *parent = 0);

    enum WorldType{DISCRETEDYNAMICSWORLD,SOFTRIGIDDYNAMICSWORLD};

    virtual WorldType type()=0;
    virtual void setType(WorldType type)=0;
    virtual qreal simulationRate()=0;
    virtual void setSimulationRate(qreal rate)=0;
    virtual void stepSimulation()=0;
    virtual QVector3D gravity()=0;
    virtual void setGravity(QVector3D gravity)=0;

    virtual void setDebug(bool debug)=0;
    virtual bool debug()=0;
    virtual QVariantList debugEntities()=0;

    virtual void addBody(PhysicsAbstractRigidBody* body)=0;
    virtual void removeBody(PhysicsAbstractRigidBody* body)=0;


};

}
#endif // PHYSICSABSTRACTDYNAMICSWORLD_H
