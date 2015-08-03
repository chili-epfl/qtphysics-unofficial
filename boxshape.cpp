#include "boxshape.h"
#include "world.h"
Bullet::BoxShape::BoxShape(QQuickItem* parent):AbstractCollitionShape(parent)
{
    m_dimension=QVector3D(1,1,1);
    init();
}
Bullet::BoxShape::~BoxShape()
{
    clean();
}

void Bullet::BoxShape::setDimension(QVector3D dimension){
    if(m_dimension!=dimension){
        m_dimension=dimension;
        clean();
        init();
    }

}
void Bullet::BoxShape::init(){
    m_shape = new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
    m_motionState = new btDefaultMotionState();
    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(0,m_motionState, m_shape, btVector3(0, 0, 0));
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);
    if(m_world)
        m_world->addRigidBody(m_rigidBody);
}

void Bullet::BoxShape::clean(){
    if(m_world)
        m_world->removeRigidBody(m_rigidBody);
    delete m_rigidBody;
    delete m_rigidBodyCI;
    delete m_motionState;
    delete m_shape;

}
