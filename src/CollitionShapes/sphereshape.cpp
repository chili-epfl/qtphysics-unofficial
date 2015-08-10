#include "sphereshape.h"
#include "src/world.h"


Bullet::SphereShape::SphereShape(QQuickItem* parent):
    AbstractCollitionShape(parent),
    m_radius(1)
{
    m_mass=1;
    init();


}
Bullet::SphereShape::~SphereShape()
{
    clear();
    if(m_world)
        m_world->removeCollitionShape(this,false);
}

void Bullet::SphereShape::init(){
    m_shape = new btSphereShape(m_radius);
    btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
    if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
        m_shape->calculateLocalInertia(m_mass,inertia);

    m_motionState = new MotionState(m_transformation,QMatrix4x4());

    connect(m_motionState,SIGNAL(motionStateChanged(QMatrix4x4)),this,SIGNAL(transformationFromBulletChanged(QMatrix4x4)));

    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(m_mass,m_motionState, m_shape,inertia);
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);
    m_rigidBody->setRestitution(m_restitution);

    m_rigidBody->setFriction(m_friction);

    m_rigidBody->setRollingFriction(m_rollingFriction);


    if(m_world)
        m_world->addRigidBody(m_rigidBody,m_group,m_mask);
}

void Bullet::SphereShape::clear(){
    if(m_world)
        m_world->removeRigidBody(m_rigidBody);
    delete m_rigidBody;
    delete m_rigidBodyCI;
    delete m_motionState;
    delete m_shape;
}

void Bullet::SphereShape::setRadius(qreal radius){
    if(m_radius!=radius){
        m_radius=radius;
        if(m_world)
            m_world->lock();
        delete m_shape;
        m_shape = new btSphereShape(m_radius);
        m_rigidBody->setCollisionShape(m_shape);
        if(m_world)
            m_world->unlock();
        emit radiusChanged(m_radius);
    }
}

void Bullet::SphereShape::setMass(qreal mass){
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
void Bullet::SphereShape::setFallInertia(QVector3D fallInertia){
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
