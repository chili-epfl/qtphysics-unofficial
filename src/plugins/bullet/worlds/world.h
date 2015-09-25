#ifndef WORLD_H
#define WORLD_H

#include <physics_entities/physicsabstractdynamicsworld.h>

#include "../bodies/abstractbody.h"

#include <QVector3D>
#include <btBulletDynamicsCommon.h>

#include "debugdraw.h"

namespace Physics {

namespace Bullet{


class World : public PhysicsAbstractDynamicsWorld
{
    Q_OBJECT

public:
    World(QObject *parent=0);
    ~World();

    WorldType type(){return m_type;}
    void setType(WorldType type);

    qreal simulationRate(){return m_simulationRate;}
    void setSimulationRate(qreal rate);

    void stepSimulation();

    QVector3D gravity(){return m_gravity;}
    void setGravity(QVector3D gravity);

    void removeBody(PhysicsAbstractRigidBody* b);
    void addBody(PhysicsAbstractRigidBody*b);

    void setDebug(bool debug);
    bool debug(){return m_debug;}
    QVariantList debugEntities(){return m_debugDraw->debug_entities;}

private slots:
    void onBodyDestroyed(QObject* obj);
    void onBodyRequireUpdate();
private:
    void removebtRigidBody(btRigidBody* b);
    void addbtRigidBody(btRigidBody* b,int group,int mask);

    void init();

    WorldType m_type;
    qreal m_simulationRate;
    QVector3D m_gravity;

    QSet<AbstractBody*> m_bodies;

    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDynamicsWorld* m_dynamicsWorld;

    bool m_debug;
    DebugDraw* m_debugDraw;


};

}}

#endif // WORLD_H

