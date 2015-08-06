#include "heightfield2d.h"
#include "src/world.h"

Bullet::HeightField2D::HeightField2D(QQuickItem* parent):AbstractCollitionShape(parent)
{
    QVector3D normal(0,1,0);
    m_normal=normal;
    m_planeConstant=1;

    init();
}

Bullet::HeightField2D::~HeightField2D()
{
    clear();
    if(m_world)
        m_world->removeCollitionShape(this,false);

}

void Bullet::HeightField2D::setPlaneConstant(qreal d){

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

}

void Bullet::HeightField2D::setNormal(QVector3D normal){

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

}
void Bullet::HeightField2D::setMass(qreal mass){
    if(m_mass!=mass){
        qWarning()<<"HeightField2D does not support mass";
    }
}
void Bullet::HeightField2D::setFallInertia(QVector3D fallInertia){
    if(m_fallInertia!=fallInertia){
        qWarning()<<"HeightField2D does not support fall inertia";
    }
}

void Bullet::HeightField2D::init(){

    m_shape = new btStaticPlaneShape(btVector3(m_normal.x(),m_normal.y(),m_normal.z()), m_planeConstant);

    m_motionState = new MotionState(m_transformation,QMatrix4x4());

    connect(m_motionState,SIGNAL(motionStateChanged(QMatrix4x4)),this,SIGNAL(transformationFromBulletChanged(QMatrix4x4)));

    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(0,m_motionState, m_shape, btVector3(0, 0, 0));

    m_rigidBody= new btRigidBody(*m_rigidBodyCI);

    m_rigidBody->setRestitution(m_restitution);

    m_rigidBody->setFriction(m_friction);

    m_rigidBody->setRollingFriction(m_rollingFriction);

    if(m_world)
        m_world->addRigidBody(m_rigidBody,m_group,m_mask);
}

void Bullet::HeightField2D::clear(){
    if(m_world)
        m_world->removeRigidBody(m_rigidBody);
    delete m_rigidBody;
    delete m_rigidBodyCI;
    delete m_motionState;
    delete m_shape;
}
