#include "heightfield2d.h"

namespace Physics {

namespace Bullet {

HeightField2D::HeightField2D(QObject* parent):
    AbstractBody(parent),
    m_normal(0,1,0),
    m_planeConstant(1.0f)
{
    setMass(0.0f);
    initShape();
    initBody();
}

HeightField2D::~HeightField2D()
{

}

void HeightField2D::setPlaneConstant(qreal d){
/*
    if(m_planeConstant!=d){
        m_planeConstant=d;
        if(m_world)
            m_world->lock();
        delete m_shape;
        m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);
        m_rigidBody->setCollisionShape(m_shape);

        if(m_world)
            m_world->unlock();

        emit planeConstantChanged(m_planeConstant);
    }
*/
}

void HeightField2D::setNormal(QVector3D normal){
/*
    if(m_normal!=normal){
        m_normal=normal;
        if(m_world)
            m_world->lock();
        delete m_shape;
        m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);
        m_rigidBody->setCollisionShape(m_shape);
        if(m_world)
            m_world->unlock();
        emit normalChanged(m_normal);
    }
*/
}
void HeightField2D::setMass(qreal mass){
    if(m_mass!=mass){
        qWarning()<<"HeightField2D does not support mass";
    }
}

void HeightField2D::initShape(){

    m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);
}

}}
