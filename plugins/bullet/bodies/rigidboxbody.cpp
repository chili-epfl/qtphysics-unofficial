#include <bodies/rigidboxbody.h>
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>

namespace Physics {

namespace Bullet {

RigidBoxBody::RigidBoxBody(QObject* parent):
    AbstractRigidBody(parent),
    m_dimension(1,1,1)

{
    initShape();
    initBody();

}
RigidBoxBody::~RigidBoxBody()
{

}

void RigidBoxBody::setDimension(QVector3D dimension){
    if(m_dimension!=dimension){
        m_dimension=dimension;
        delete m_shape;
        m_shape=new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
        m_rigidBody->setCollisionShape(m_shape);
        setMassProps();
    }
}
void RigidBoxBody::initShape(){
    m_shape = new btBoxShape(btVector3(m_dimension.x()/2,m_dimension.y()/2,m_dimension.z()/2));
}

}}


