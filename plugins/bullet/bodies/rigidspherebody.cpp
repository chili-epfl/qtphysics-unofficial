#include "rigidspherebody.h"

#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>

namespace Physics {


namespace Bullet {


RigidSphereBody::RigidSphereBody(QObject* parent):
    AbstractRigidBody(parent),
    m_radius(1)
{
    initShape();
    initBody();
}
RigidSphereBody::~RigidSphereBody()
{

}

void RigidSphereBody::initShape(){
    m_shape = new btSphereShape(m_radius);
}



void RigidSphereBody::setRadius(qreal radius){
    if(m_radius!=radius){
        m_radius=radius;
        delete m_shape;
        m_shape = new btSphereShape(m_radius);
        m_rigidBody->setCollisionShape(m_shape);
        setMassProps();
    }
}


}}
