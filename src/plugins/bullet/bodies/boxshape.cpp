#include "boxshape.h"
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>

namespace Physics {

namespace Bullet {

BoxShape::BoxShape(QObject* parent):
    AbstractBody(parent),
    m_dimension(1,1,1)

{
    initShape();
    initBody();

}
BoxShape::~BoxShape()
{

}

void BoxShape::setDimension(QVector3D dimension){
    if(m_dimension!=dimension){
        m_dimension=dimension;
        delete m_shape;
        m_shape=new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
        m_rigidBody->setCollisionShape(m_shape);
        setMassProps();
    }
}
void BoxShape::initShape(){
    m_shape = new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
}

}}


