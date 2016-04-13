#include <worlds/dynamicsworld.h>
namespace Physics {

namespace Bullet{

DynamicsWorld::DynamicsWorld(QObject *parent):
    PhysicsAbstractDynamicsWorld(parent)
{
    m_simulationRate=60.0;
    m_scaleFactor=1.0;
    m_gravity=QVector3D(0,0,0);
    init();
}

DynamicsWorld::~DynamicsWorld()
{

    for(AbstractRigidBody* c: m_PhysicsBodies2BulletBodies.keys()){
        removeRigidBody(c);
        delete c;
    }
    delete m_dynamicsWorld;
    delete m_solver;
    delete m_collisionConfiguration;
    delete m_dispatcher;
    delete m_broadphase;

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

void DynamicsWorld::setScaleFactor(qreal val)
{
    if(m_scaleFactor!=val){
         m_scaleFactor=val;
         //remove all the objects. Next iteration will create them back
         for(AbstractRigidBody* c: m_PhysicsBodies2BulletBodies.keys()){
             removeRigidBody(c);
             delete c;
         }
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
   }
}


void DynamicsWorld::onBodyDestroyed(QObject* obj){
//    btRigidBody* btBody= (btRigidBody*)m_PhysicsBodies2BulletBodies[(AbstractRigidBody*)obj];
//    m_PhysicsBodies2BulletBodies.remove((AbstractRigidBody*)obj);
//    m_BulletBodies2PhysicsBodies.remove(btBody);
//    removebtRigidBody(btBody);
}

void DynamicsWorld::removebtRigidBody(btRigidBody* b){
    m_dynamicsWorld->removeRigidBody(b);
}
void DynamicsWorld::addbtRigidBody(btRigidBody* b,int group,int mask){
    m_dynamicsWorld->addRigidBody(b,group,mask);
}


QVector<DynamicsWorld::Collision> DynamicsWorld::getCollisions(){
    QVector<DynamicsWorld::Collision> collisions;
    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i=0;i<numManifolds;i++)
    {
        btPersistentManifold* contactManifold =  m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
        btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

        Collision collision;
        collision.body1=m_BulletBodies2PhysicsBodies[obA];
        collision.body2=m_BulletBodies2PhysicsBodies[obB];

        int numContacts = contactManifold->getNumContacts();
        for (int j=0;j<numContacts;j++)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            if (pt.getDistance()<0.5f)
            {
                collision.pointOnBody1= QVector3D(pt.getPositionWorldOnA().x(),pt.getPositionWorldOnA().y(),pt.getPositionWorldOnA().z());
                collision.pointOnBody2=QVector3D(pt.getPositionWorldOnB().x(),pt.getPositionWorldOnB().y(),pt.getPositionWorldOnB().z());
                collision.pointOnBody1Local= QVector3D(pt.m_localPointA.x(),pt.m_localPointA.y(),pt.m_localPointA.z());
                collision.pointOnBody2Local=QVector3D(pt.m_localPointB.x(),pt.m_localPointB.y(),pt.m_localPointB.z());
                collisions.append(collision);
                break;
                //const btVector3& ptA = pt.getPositionWorldOnA();
                //const btVector3& ptB = pt.getPositionWorldOnB();
                //const btVector3& normalOnB = pt.m_normalWorldOnB;
            }
        }
    }
    return collisions;
}


}

}
