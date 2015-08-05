#include "abstractcollitionshape.h"
#include "src/world.h"

Bullet::AbstractCollitionShape::AbstractCollitionShape(QQuickItem* parent):QQuickItem(parent)
{
    m_world=0;
    m_group=1;
    m_mask=1;
    m_transformation=QMatrix4x4();

    m_mass=0;
    m_fallInertia=QVector3D(0,0,0);

}

void Bullet::AbstractCollitionShape::setWorld(Bullet::World* world){

    m_world=world;
    m_world->addCollitionShape(this,false);
    m_world->addRigidBody(m_rigidBody,m_group,m_mask);
}

void Bullet::AbstractCollitionShape::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        if(m_world){
            m_world->removeRigidBody(m_rigidBody,true);
            m_world->addRigidBody(m_rigidBody,m_group,m_mask);
        }
    }
}

void Bullet::AbstractCollitionShape::setGroup(int group){
    if(group >0 && m_group!=group){
        if(m_world){
            m_world->removeRigidBody(m_rigidBody,true);
            m_world->addRigidBody(m_rigidBody,m_group,m_mask);
        }
    }
}

QMatrix4x4 Bullet::AbstractCollitionShape::transformationFromBullet(){
    return m_motionState->getWorldTransformAsQMatrix4x4();
}

void Bullet::AbstractCollitionShape::setTransformation(QMatrix4x4 m){
    if(m_world){
        m_world->lock();
        m_motionState->setWorldTransform(m);
        m_rigidBody->setMotionState(m_motionState);
        m_world->unlock();
    }
    m_transformation=m;
}

void Bullet::AbstractCollitionShape::setMass(qreal mass){
    if(m_mass!=mass){
        m_mass=mass;
        emit massChanged(m_mass);
    }
}
void Bullet::AbstractCollitionShape::setFallInertia(QVector3D fallInertia){
    if(m_fallInertia!=fallInertia){
        m_fallInertia=fallInertia;
        emit fallInertiaChanged(m_fallInertia);
    }
}

