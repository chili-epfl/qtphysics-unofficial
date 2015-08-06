#include "convexhullshape.h"
#include "src/world.h"

Bullet::ConvexHullShape::ConvexHullShape(QQuickItem* parent):AbstractCollitionShape(parent)
{
    m_mass=1;
    init();

}

Bullet::ConvexHullShape::~ConvexHullShape(){
    clear();
    m_world->removeCollitionShape(this,false);

}


void Bullet::ConvexHullShape::init(){
    /*m_shape = new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
    m_shape->calculateLocalInertia(m_mass,btVector3(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z()));

m_motionState = new MotionState(m_transformation,QMatrix4x4());
    connect(m_motionState,SIGNAL(motionStateChanged(QMatrix4x4)),this,SIGNAL(transformationFromBulletChanged(QMatrix4x4)));

    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(m_mass,m_motionState, m_shape, btVector3(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z()));
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);
    if(m_world)
        m_world->addRigidBody(m_rigidBody);*/
}


void Bullet::ConvexHullShape::clear(){
    if(m_world)
        m_world->removeRigidBody(m_rigidBody);
    delete m_rigidBody;
    delete m_rigidBodyCI;
    delete m_motionState;
    delete m_shape;

}
