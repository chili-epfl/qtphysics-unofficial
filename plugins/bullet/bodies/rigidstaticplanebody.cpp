#include <bodies/rigidstaticplanebody.h>

namespace Physics {

namespace Bullet {

RigidStaticPlaneBody::RigidStaticPlaneBody(QObject* parent):
    AbstractRigidBody(parent),
    m_normal(0,1,0),
    m_planeConstant(0.0f)
{
    setMass(0.0f);
    initShape();
    initBody();
}

RigidStaticPlaneBody::~RigidStaticPlaneBody()
{

}

void RigidStaticPlaneBody::setPlaneConstant(qreal d){
    if(m_planeConstant!=d){
        m_planeConstant=d;      
        delete m_shape;
        m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);
        m_rigidBody->setCollisionShape(m_shape);
        setMassProps();
    }
}

void RigidStaticPlaneBody::setNormal(QVector3D normal){
    if(m_normal!=normal){
        m_normal=normal;
        delete m_shape;
        m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);
        m_rigidBody->setCollisionShape(m_shape);
        setMassProps();
    }
}
void RigidStaticPlaneBody::setMass(qreal mass){
    if(m_mass!=mass){
        qWarning()<<"RigidStaticPlaneBody does not support mass";
    }
}

void RigidStaticPlaneBody::initShape(){
    m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);
}

}}
