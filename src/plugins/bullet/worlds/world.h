#ifndef WORLD_H
#define WORLD_H

#include <physics_entities/physicsabstractdynamicsworld.h>

#include "../bodies/abstractbody.h"


#include <QVector3D>
#include <btBulletDynamicsCommon.h>
namespace Physics {

namespace Bullet{


class World : public PhysicsAbstractDynamicsWorld
{
    Q_OBJECT

public:
    enum WorldType{DISCRETEDYNAMICSWORLD,SOFTRIGIDDYNAMICSWORLD};

    WorldType type(){return m_type;}
    void setType(WorldType type);

    qreal simulationRate(){return m_simulationRate;}
    void setSimulationRate(qreal rate);

    QVector3D gravity(){return m_gravity;}
    void setGravity(QVector3D gravity);

    void removebtRigidBody(btRigidBody* b,bool emitSignal=true);
    void addbtRigidBody(btRigidBody* b,int group,int mask,bool emitSignal=true);
    void removeBody(AbstractBody* b,bool emitSignal=true);
    void addBody(AbstractBody* b,bool emitSignal=true);

private:

    void init();

    WorldType m_type;
    qreal m_simulationRate;
    QVector3D m_gravity;



    QHash<QString, AbstractBody*> m_bodies;



    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDynamicsWorld* m_dynamicsWorld;

};

}}

#endif // WORLD_H

