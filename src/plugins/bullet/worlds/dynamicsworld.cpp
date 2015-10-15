#include "dynamicsworld.h"
namespace Physics {

namespace Bullet{

DynamicsWorld::DynamicsWorld(QObject *parent):
    PhysicsAbstractDynamicsWorld(parent)
{
    m_simulationRate=60.0;
    m_gravity=QVector3D(0,-10,0);
    init();
}

DynamicsWorld::~DynamicsWorld()
{
/*
    for(AbstractRigidBody* c: m_collitionShapes.values())
        delete c;

    delete m_simThread;

    delete m_dynamicsWorld;
    delete m_solver;
    delete m_collisionConfiguration;
    delete m_dispatcher;
    delete m_broadphase;
*/
}

void DynamicsWorld::init(){

    m_broadphase = new btDbvtBroadphase();
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_solver = new btSequentialImpulseConstraintSolver;

   m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

   m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));

}

void DynamicsWorld::setSimulationRate(qreal rate){
    if(m_simulationRate!=rate){
        m_simulationRate=rate;
    }
}

void DynamicsWorld::stepSimulation(){
    m_dynamicsWorld->stepSimulation(1.0f/m_simulationRate);
    if(m_debug){
        //m_debugDraw->debug_entities.clear();
        //m_dynamicsWorld->debugDrawWorld();
    }

}

void DynamicsWorld::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));
    }
}
void DynamicsWorld::setDebug(bool debug){
    if(m_debug!=debug){
        m_debug=debug;
    }
}


void DynamicsWorld::removeRigidBody(PhysicsAbstractRigidBody* c){
    if(!c->inherits("Physics::Bullet::AbstractRigidBody"))
        qWarning("The body was defined with a plugin different from Bullet");
     else{
        Physics::Bullet::AbstractRigidBody* c_cast=static_cast<Physics::Bullet::AbstractRigidBody*>(c);
        m_PhysicsBodies2BulletBodies.remove(c_cast);
        m_BulletBodies2PhysicsBodies.remove(c_cast->bulletBody());
        removebtRigidBody(c_cast->bulletBody());
    }
}
void DynamicsWorld::addRigidBody(PhysicsAbstractRigidBody* c){
   if(!c->inherits("Physics::Bullet::AbstractRigidBody"))
       qWarning("The body was defined with a plugin different from Bullet");
    else{
       Physics::Bullet::AbstractRigidBody* c_cast=static_cast<Physics::Bullet::AbstractRigidBody*>(c);
       m_PhysicsBodies2BulletBodies[c_cast]=c_cast->bulletBody();
       m_BulletBodies2PhysicsBodies[c_cast->bulletBody()]=c_cast;
       addbtRigidBody(c_cast->bulletBody(),c_cast->group(),c_cast->mask());
       connect(c,SIGNAL(destroyed(QObject*)),this,SLOT(onBodyDestroyed(QObject*)));
       connect(c_cast,SIGNAL(worldUpdateRequired()),this,SLOT(onBodyRequireUpdate()));
   }
}
void DynamicsWorld::onBodyRequireUpdate(){
    QObject* sender=QObject::sender();
    if(sender->inherits("Physics::Bullet::AbstractRigidBody")){
        Physics::Bullet::AbstractRigidBody* sender_cast=static_cast<Physics::Bullet::AbstractRigidBody*>(sender);
        removebtRigidBody(sender_cast->bulletBody());
        addbtRigidBody(sender_cast->bulletBody(),sender_cast->group(),sender_cast->mask());
    }

}


void DynamicsWorld::onBodyDestroyed(QObject* obj){
    if(obj->inherits("PhysicsAbstractRigidBody"))
        removeRigidBody(static_cast<PhysicsAbstractRigidBody*>(obj));
}

void DynamicsWorld::removebtRigidBody(btRigidBody* b){
    m_dynamicsWorld->removeRigidBody(b);
}
void DynamicsWorld::addbtRigidBody(btRigidBody* b,int group,int mask){
    m_dynamicsWorld->addRigidBody(b,group,mask);
}


QVector<DynamicsWorld::Collision> DynamicsWorld::getCollisions(){
    QVector<DynamicsWorld::Collision> collitions;
    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i=0;i<numManifolds;i++)
    {
        btPersistentManifold* contactManifold =  m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
        btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

        Collision collition;
        collition.body1=m_BulletBodies2PhysicsBodies[obA];
        collition.body2=m_BulletBodies2PhysicsBodies[obB];

        int numContacts = contactManifold->getNumContacts();
        for (int j=0;j<numContacts;j++)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            if (pt.getDistance()<0.5f)
            {
                collition.pointOnBody1= QVector3D(pt.getPositionWorldOnA().x(),pt.getPositionWorldOnA().y(),pt.getPositionWorldOnA().z());
                collition.pointOnBody2=QVector3D(pt.getPositionWorldOnB().x(),pt.getPositionWorldOnB().y(),pt.getPositionWorldOnB().z());
                collitions.append(collition);
                break;
                //const btVector3& ptA = pt.getPositionWorldOnA();
                //const btVector3& ptB = pt.getPositionWorldOnB();
                //const btVector3& normalOnB = pt.m_normalWorldOnB;
            }
        }
    }
    return collitions;
}


}

}
