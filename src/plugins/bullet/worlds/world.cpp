#include "world.h"
namespace Physics {

namespace Bullet{

World::World(QObject *parent):
    PhysicsAbstractDynamicsWorld(parent)
{

    m_type=DISCRETEDYNAMICSWORLD;
    m_simulationRate=60.0;
    m_gravity=QVector3D(0,-10,0);
    m_debugDraw=new DebugDraw();
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
    case DISCRETEDYNAMICSWORLD:
        m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
        break;
    case SOFTRIGIDDYNAMICSWORLD:

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

void World::stepSimulation(){
    m_dynamicsWorld->stepSimulation(1.0f/m_simulationRate,10);
    if(m_debug){
        //m_debugDraw->debug_entities.clear();
        //m_dynamicsWorld->debugDrawWorld();
    }

}


void World::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));
    }
}
void World::setDebug(bool debug){
    if(m_debug!=debug){
        m_debug=debug;
        if(m_debug)
            m_dynamicsWorld->setDebugDrawer(m_debugDraw);
        else
            m_dynamicsWorld->setDebugDrawer(Q_NULLPTR);
    }

}


void World::removeBody(PhysicsAbstractRigidBody* c){
    if(!c->inherits("Physics::Bullet::AbstractBody"))
        qWarning("The body was defined with a plugin different from Bullet");
     else{
        Physics::Bullet::AbstractBody* c_cast=static_cast<Physics::Bullet::AbstractBody*>(c);
        m_bodies.remove(c_cast);
        removebtRigidBody(c_cast->bulletBody());
    }
}
void World::addBody(PhysicsAbstractRigidBody* c){
   if(!c->inherits("Physics::Bullet::AbstractBody"))
       qWarning("The body was defined with a plugin different from Bullet");
    else{
       Physics::Bullet::AbstractBody* c_cast=static_cast<Physics::Bullet::AbstractBody*>(c);
       m_bodies.insert(c_cast);
       addbtRigidBody(c_cast->bulletBody(),c_cast->group(),c_cast->mask());
       connect(c,SIGNAL(destroyed(QObject*)),this,SLOT(onBodyDestroyed(QObject*)));
       connect(c_cast,SIGNAL(worldUpdateRequired()),this,SLOT(onBodyRequireUpdate()));
   }
}
void World::onBodyRequireUpdate(){
    QObject* sender=QObject::sender();
    if(sender->inherits("Physics::Bullet::AbstractBody")){
        Physics::Bullet::AbstractBody* sender_cast=static_cast<Physics::Bullet::AbstractBody*>(sender);
        removebtRigidBody(sender_cast->bulletBody());
        addbtRigidBody(sender_cast->bulletBody(),sender_cast->group(),sender_cast->mask());
    }

}


void World::onBodyDestroyed(QObject* obj){
    if(obj->inherits("PhysicsAbstractRigidBody"))
        removeBody(static_cast<PhysicsAbstractRigidBody*>(obj));
}

void World::removebtRigidBody(btRigidBody* b){
    m_dynamicsWorld->removeRigidBody(b);
}
void World::addbtRigidBody(btRigidBody* b,int group,int mask){
    m_dynamicsWorld->addRigidBody(b,group,mask);
}
}}
