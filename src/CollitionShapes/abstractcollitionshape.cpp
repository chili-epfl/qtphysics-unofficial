#include "abstractcollitionshape.h"
#include "src/world.h"

Bullet::AbstractCollitionShape::AbstractCollitionShape(QQuickItem* parent):QQuickItem(parent)
{
    m_world=0;
    m_group=1;
    m_mask=1;
    m_transformation=QMatrix4x4();

    m_restitution=0.0f;
    m_friction=0.0f;
    m_rollingFriction=0.0f;

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



void Bullet::AbstractCollitionShape::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        if(m_world)
            m_world->lock();
        m_rigidBody->setRestitution(m_restitution);
        if(m_world)
            m_world->unlock();
    }
}
void Bullet::AbstractCollitionShape::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        if(m_world)
            m_world->lock();
        m_rigidBody->setRollingFriction(m_rollingFriction);
        if(m_world)
            m_world->unlock();
    }
}
void Bullet::AbstractCollitionShape::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        if(m_world)
            m_world->lock();
        m_rigidBody->setFriction(m_friction);
        if(m_world)
            m_world->unlock();
    }
}

void Bullet::AbstractCollitionShape::applyForce(QVector3D force,QVector3D relationPosition){
    if(m_world)
        m_world->lock();
    m_rigidBody->applyForce(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
    if(m_world)
        m_world->unlock();
}

void Bullet::AbstractCollitionShape::applyImpulse(QVector3D force,QVector3D relationPosition){
    if(m_world)
        m_world->lock();
    m_rigidBody->applyImpulse(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
    if(m_world)
        m_world->unlock();

}
void Bullet::AbstractCollitionShape::clearForces(){
    if(m_world)
        m_world->lock();
    m_rigidBody->clearForces();
    if(m_world)
        m_world->unlock();

}

