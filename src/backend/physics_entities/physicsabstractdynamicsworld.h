#ifndef PHYSICSABSTRACTDYNAMICSWORLD_H
#define PHYSICSABSTRACTDYNAMICSWORLD_H
#include "backend_global.h"

#include "physicsabstractrigidbody.h"
#include <QObject>
#include <QVector3D>
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
        QVector3D normalBody2;

        Collision& operator=(const Collision& c)
         {
             body1=c.body1;
             body2=c.body2;
             pointOnBody1=c.pointOnBody1;
             pointOnBody2=c.pointOnBody2;
             normalBody2=c.normalBody2;
             return *this;
        }
        inline bool operator==(const Collision& c) const
        {
            return (body1 == c.body1 && body2 == c.body2);
        }
        inline uint qHash(const Collision &key, uint seed)
        {
            return qHash(*(key.body1), seed) ^ qHash(*(key.body2), seed);
        }

    };

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

    virtual void addBody(PhysicsAbstractRigidBody* body)=0;
    virtual void removeBody(PhysicsAbstractRigidBody* body)=0;

    virtual QVector<Collision> getCollisions()=0;

};

}
#endif // PHYSICSABSTRACTDYNAMICSWORLD_H
