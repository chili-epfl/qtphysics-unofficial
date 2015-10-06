#ifndef DYNAMICSWORLD_H
#define DYNAMICSWORLD_H

#include <physics_entities/physicsabstractdynamicsworld.h>

#include "../bodies/abstractrigidbody.h"

#include <QVector3D>
#include <btBulletDynamicsCommon.h>

namespace Physics {

namespace Bullet{


class DynamicsWorld : public PhysicsAbstractDynamicsWorld
{
    Q_OBJECT

public:
    DynamicsWorld(QObject *parent=0);
    ~DynamicsWorld();

    qreal simulationRate(){return m_simulationRate;}
    void setSimulationRate(qreal rate);

    void stepSimulation();

    QVector3D gravity(){return m_gravity;}
    void setGravity(QVector3D gravity);

    void removeRigidBody(PhysicsAbstractRigidBody* b);
    void addRigidBody(PhysicsAbstractRigidBody*b);

    void setDebug(bool debug);
    bool debug(){return m_debug;}

    QVector<Collision> getCollisions();


private slots:
    void onBodyDestroyed(QObject* obj);
    void onBodyRequireUpdate();
private:
    void removebtRigidBody(btRigidBody* b);
    void addbtRigidBody(btRigidBody* b,int group,int mask);

    void init();

    qreal m_simulationRate;
    QVector3D m_gravity;

    QHash<AbstractRigidBody*,btCollisionObject*> m_PhysicsBodies2BulletBodies;
    QHash<btCollisionObject*,AbstractRigidBody*> m_BulletBodies2PhysicsBodies;

    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDynamicsWorld* m_dynamicsWorld;

    bool m_debug;

};

}}

#endif // DYNAMICSWORLD_H

