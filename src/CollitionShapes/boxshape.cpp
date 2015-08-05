#include "boxshape.h"
#include "src/world.h"
Bullet::BoxShape::BoxShape(QQuickItem* parent):AbstractCollitionShape(parent)
{
    m_dimension=QVector3D(1,1,1);
    m_mass=1;
    init();

}
Bullet::BoxShape::~BoxShape()
{
    clean();
    if(m_world)
        m_world->removeCollitionShape(this,false);
}

void Bullet::BoxShape::setDimension(QVector3D dimension){
    if(m_dimension!=dimension){        
        m_dimension=dimension;
        if(m_world)
            m_world->lock();
        delete m_shape;
        m_shape=new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
        m_rigidBody->setCollisionShape(m_shape);
        if(m_world)
            m_world->unlock();
        emit dimensionChanged(m_dimension);
    }

}
void Bullet::BoxShape::init(){
    m_shape = new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
    btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
    if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
        m_shape->calculateLocalInertia(m_mass,inertia);
    m_motionState = new MotionState(m_transformation,QMatrix4x4());
    connect(m_motionState,SIGNAL(motionStateChanged(QMatrix4x4)),this,SIGNAL(transformationFromBulletChanged(QMatrix4x4)));
    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(m_mass,m_motionState, m_shape, btVector3(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z()));
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);
    if(m_world)
        m_world->addRigidBody(m_rigidBody,m_group,m_mask);
}

void Bullet::BoxShape::clean(){
    if(m_world)
        m_world->removeRigidBody(m_rigidBody);
    delete m_rigidBody;
    delete m_rigidBodyCI;
    delete m_motionState;
    delete m_shape;

}

void Bullet::BoxShape::setMass(qreal mass){
    if(m_mass!=mass){
        m_mass=mass;
        if(m_world)
            m_world->lock();
        m_rigidBody->setMassProps(m_mass,btVector3(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z()));
        if(m_world)
            m_world->unlock();
        emit massChanged(m_mass);
    }
}
void Bullet::BoxShape::setFallInertia(QVector3D fallInertia){
    if(m_fallInertia!=fallInertia){
        m_fallInertia=fallInertia;
        if(m_world)
            m_world->lock();
        m_rigidBody->setMassProps(m_mass,btVector3(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z()));
        if(m_world)
            m_world->unlock();
        emit fallInertiaChanged(m_fallInertia);
    }
}


