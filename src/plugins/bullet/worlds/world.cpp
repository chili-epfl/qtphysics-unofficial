#include "world.h"
namespace Physics {

namespace Bullet{

World::World(QObject *parent):
    PhysicsAbstractDynamicsWorld(parent)
{

    m_type=DISCRETEDYNAMICSWORLD;
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
    }
}


void World::removeBody(PhysicsAbstractRigidBody* c){
    if(!c->inherits("Physics::Bullet::AbstractBody"))
        qWarning("The body was defined with a plugin different from Bullet");
     else{
        Physics::Bullet::AbstractBody* c_cast=static_cast<Physics::Bullet::AbstractBody*>(c);
        m_PhysicsBodies2BulletBodies.remove(c_cast);
        m_BulletBodies2PhysicsBodies.remove(c_cast->bulletBody());
        removebtRigidBody(c_cast->bulletBody());
    }
}
void World::addBody(PhysicsAbstractRigidBody* c){
   if(!c->inherits("Physics::Bullet::AbstractBody"))
       qWarning("The body was defined with a plugin different from Bullet");
    else{
       Physics::Bullet::AbstractBody* c_cast=static_cast<Physics::Bullet::AbstractBody*>(c);
       m_PhysicsBodies2BulletBodies[c_cast]=c_cast->bulletBody();
       m_BulletBodies2PhysicsBodies[c_cast->bulletBody()]=c_cast;
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


QVector<World::Collision> World::getCollisions(){
    QVector<World::Collision> collitions;

    Q_FOREACH(Collision c, m_collitions.keys())
        m_collitions[c]=0;

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
            if (pt.getDistance()<0.f)
            {
                if(m_collitions.contains(collition)){
                    m_collitions[collition]=1;
                }
                else{
                    m_collitions[collition]=2;
                }
                break;
                //const btVector3& ptA = pt.getPositionWorldOnA();
                //const btVector3& ptB = pt.getPositionWorldOnB();
                //const btVector3& normalOnB = pt.m_normalWorldOnB;
            }
        }
    }

    Q_FOREACH(Collision c, m_collitions.keys()){
        if(m_collitions[c]==0){
            m_collitions.remove(c);
        }
        else if(m_collitions[c]==2){
            collitions.append(c);
        }
    }

    return collitions;
}


}

}
