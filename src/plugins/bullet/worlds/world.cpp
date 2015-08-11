#include "world.h"
namespace Physics {

namespace Bullet{

World::World(QObject *parent):
    QObject(parent)
{

    m_type=WorldType::DISCRETEDYNAMICSWORLD;
    m_simulationRate=60.0;
    m_gravity=QVector3D(0,-10,0);
    init();
}

World::~World()
{
/*
    for(AbstractBody* c: m_collitionShapes.values())
        delete c;

    delete m_simThread;

    delete m_dynamicsWorld;
    delete m_solver;
    delete m_collisionConfiguration;
    delete m_dispatcher;
    delete m_broadphase;
*/
}

void World::init(){

    m_broadphase = new btDbvtBroadphase();
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

    m_solver = new btSequentialImpulseConstraintSolver;

    switch (m_type) {
    case WorldType::DISCRETEDYNAMICSWORLD:
        m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
        break;
    case WorldType::SOFTRIGIDDYNAMICSWORLD:

        break;
    default:
        qFatal("Bullet: unknown world type");
        break;
    }

    m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));

}

void World::setType(WorldType type){
    if(m_type!=type){
        m_type=type;
    }
}

void World::setSimulationRate(qreal rate){
    if(m_simulationRate!=rate){
        m_simulationRate=rate;
    }
}

void World::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));
    }
}



void World::removeBody(AbstractBody* c,bool emitSignal){
    m_bodies.remove(c->objectName());
}
void World::addBody(AbstractBody* c,bool emitSignal){
   m_bodies[c->objectName()]=c;

}

void World::removebtRigidBody(btRigidBody* b,bool emitSignal){
    m_dynamicsWorld->removeRigidBody(b);
}
void World::addbtRigidBody(btRigidBody* b,int group,int mask,bool emitSignal){
    m_dynamicsWorld->addRigidBody(b,group,mask);
}
}}
