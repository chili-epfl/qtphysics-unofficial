#include "sphereshape.h"
#include "world.h"


Bullet::SphereShape::SphereShape(QQuickItem* parent):AbstractCollitionShape(parent)
{
    m_radius=1;
    init();
}
Bullet::SphereShape::~SphereShape()
{
    clean();
}


void Bullet::SphereShape::init(){
    m_shape = new btSphereShape(m_radius);
    m_motionState = new btDefaultMotionState();
    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(0,m_motionState, m_shape, btVector3(0, 0, 0));
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);
    if(m_world)
        m_world->addRigidBody(m_rigidBody);
}

void Bullet::SphereShape::clean(){
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
        clean();
        init();
        emit radiusChanged(m_radius);
    }
}
