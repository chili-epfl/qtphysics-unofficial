#include "abstractbody.h"
#include "src/world.h"

Bullet::AbstractBody::AbstractBody(QQuickItem* parent):
    QQuickItem(parent),
    m_world(0),
    m_group(1),
    m_mask(1),
    m_worldTransformation(),
    m_restitution(0.0f),
    m_friction(0.0f),
    m_rollingFriction(0.0f),
    m_fallInertia(),
    m_mass(0),
    m_kinematic(false)
{
    /*QQuickItem* parent is the visual parent(http://doc.qt.io/qt-5/qtquick-visualcanvas-visualparent.html)
     *It's null unless the object is created inside an Item */
    if(parent && parent->inherits("Bullet::World"))
        m_world=qobject_cast<Bullet::World*>(parent);

    connect(this,SIGNAL(parentChanged(QQuickItem*)),this,SLOT(onParentChanged(QQuickItem*)));
}

void Bullet::AbstractBody::onParentChanged(QQuickItem* parent){
    if(parent && parent->inherits("Bullet::World"))
        setWorld(qobject_cast<Bullet::World*>(parent));
}


void Bullet::AbstractBody::setWorld(Bullet::World* world){
    m_world=world;
    m_world->addBody(this,false);
    m_world->addbtRigidBody(m_rigidBody,m_group,m_mask);
}

void Bullet::AbstractBody::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        if(m_world){
            m_world->removebtRigidBody(m_rigidBody,true);
            m_world->addbtRigidBody(m_rigidBody,m_group,m_mask);
        }
    }
}

void Bullet::AbstractBody::setGroup(int group){
    if(group >0 && m_group!=group){
        if(m_world){
            m_world->removebtRigidBody(m_rigidBody,true);
            m_world->addbtRigidBody(m_rigidBody,m_group,m_mask);
        }
    }
}

QMatrix4x4 Bullet::AbstractBody::transformationFromBullet(){
    return m_motionState->getWorldTransformAsQMatrix4x4();
}

void Bullet::AbstractBody::setTransformation(QMatrix4x4 m){
    if(m_world){
        m_world->lock();
        m_motionState->setWorldTransform(m);
        m_rigidBody->setMotionState(m_motionState);
        m_world->unlock();
    }
    m_transformation=m;
}



void Bullet::AbstractBody::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        if(m_world)
            m_world->lock();
        m_rigidBody->setRestitution(m_restitution);
        if(m_world)
            m_world->unlock();
    }
}
void Bullet::AbstractBody::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        if(m_world)
            m_world->lock();
        m_rigidBody->setRollingFriction(m_rollingFriction);
        if(m_world)
            m_world->unlock();
    }
}
void Bullet::AbstractBody::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        if(m_world)
            m_world->lock();
        m_rigidBody->setFriction(m_friction);
        if(m_world)
            m_world->unlock();
    }
}

void Bullet::AbstractBody::applyForce(QVector3D force,QVector3D relationPosition){
    if(m_world)
        m_world->lock();
    m_rigidBody->applyForce(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
    if(m_world)
        m_world->unlock();
}

void Bullet::AbstractBody::applyImpulse(QVector3D force,QVector3D relationPosition){
    if(m_world)
        m_world->lock();
    m_rigidBody->applyImpulse(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
    if(m_world)
        m_world->unlock();

}
void Bullet::AbstractBody::clearForces(){
    if(m_world)
        m_world->lock();
    m_rigidBody->clearForces();
    if(m_world)
        m_world->unlock();

}

void Bullet::AbstractBody::setKinematic(bool kinematic){
    if(m_kinematic!=kinematic){
        //m_kinematic=kinematic;
        qWarning()<<"Kinematic is not yet supported";
    }
}

