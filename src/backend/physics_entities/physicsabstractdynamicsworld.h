#ifndef PHYSICSABSTRACTDYNAMICSWORLD_H
#define PHYSICSABSTRACTDYNAMICSWORLD_H
#include <qtphysicsunofficial_global.h>

#include <backend/physics_entities/physicsabstractrigidbody.h>
namespace Physics {

class PhysicsAbstractDynamicsWorld : public QObject
{
    Q_OBJECT
public:

    struct Collision{
        PhysicsAbstractRigidBody* body1;
        PhysicsAbstractRigidBody* body2;
        QVector3D pointOnBody1;
        QVector3D pointOnBody2;
        QVector3D pointOnBody1Local;
        QVector3D pointOnBody2Local;
        QVector3D normalBody2;

     };

    explicit PhysicsAbstractDynamicsWorld(QObject *parent = 0);

    enum WorldType{DISCRETEDYNAMICSWORLD,SOFTRIGIDDYNAMICSWORLD};

    virtual WorldType type(){return DISCRETEDYNAMICSWORLD;}

    virtual qreal simulationRate()=0;
    virtual void setSimulationRate(qreal rate)=0;
    virtual void stepSimulation()=0;
    virtual QVector3D gravity()=0;
    virtual void setGravity(QVector3D gravity)=0;

    virtual void setDebug(bool debug)=0;
    virtual bool debug()=0;

    virtual void addRigidBody(PhysicsAbstractRigidBody* body)=0;
    virtual void removeRigidBody(PhysicsAbstractRigidBody* body)=0;

    virtual QVector<Collision> getCollisions()=0;

};

}
#endif // PHYSICSABSTRACTDYNAMICSWORLD_H
