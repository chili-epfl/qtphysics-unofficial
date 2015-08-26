#include "sphereshape.h"

#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>

namespace Physics {


namespace Bullet {


SphereShape::SphereShape(QObject* parent):
    AbstractBody(parent),
    m_radius(1)
{
    initShape();
    initBody();
}
SphereShape::~SphereShape()
{

}

void SphereShape::initShape(){
    m_shape = new btSphereShape(m_radius);
}



void SphereShape::setRadius(qreal radius){
    /*if(m_radius!=radius){
        m_radius=radius;
        if(m_world)
            m_world->lock();
        delete m_shape;
        m_shape = new btSphereShape(m_radius);
        m_rigidBody->setCollisionShape(m_shape);
        if(m_world)
            m_world->unlock();
        emit radiusChanged(m_radius);
    }*/
}


}}
