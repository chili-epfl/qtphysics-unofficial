#include "boxshape.h"
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>

namespace Physics {

namespace Bullet {

BoxShape::BoxShape(QObject* parent):
    AbstractBody(parent),
    m_dimension(1,1,1)

{
    setMass(1.0f);
    initShape();
    initBody();

}
BoxShape::~BoxShape()
{

}

void BoxShape::setDimension(QVector3D dimension){
    /*if(m_dimension!=dimension){
        m_dimension=dimension;
        if(m_world)
            m_world->lock();
        delete m_shape;
        m_shape=new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
        btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
        m_shape->calculateLocalInertia(m_mass,inertia);
        m_rigidBody->setCollisionShape(m_shape);
        if(m_world)
            m_world->unlock();
        emit dimensionChanged(m_dimension);
    }*/

}
void BoxShape::initShape(){
    m_shape = new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
}


}}


