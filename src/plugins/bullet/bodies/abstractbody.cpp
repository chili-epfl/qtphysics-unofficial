#include "abstractbody.h"
#include "motionstate.h"
namespace Physics {

namespace Bullet {

AbstractBody::AbstractBody(QObject* parent):
    PhysicsAbstractRigidBody(parent),
    m_mask(1),
    m_group(1),
    m_changeFlags(NoChange),
    m_mass(0),
    m_fallInertia(),
    m_restitution(0.0f),
    m_friction(0.0f),
    m_rollingFriction(0.0f)
{
    m_shape=Q_NULLPTR;
    m_motionState=Q_NULLPTR;
    m_rigidBody=Q_NULLPTR;
}

void AbstractBody::initBody(){

    btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
    if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
        m_shape->calculateLocalInertia(m_mass,inertia);

    m_motionState = new MotionState(QMatrix4x4(),QMatrix4x4());
    btRigidBody::btRigidBodyConstructionInfo* m_rigidBodyCI=
            new btRigidBody::btRigidBodyConstructionInfo(m_mass,m_motionState, m_shape,
                                                         btVector3(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z()));
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);

    m_rigidBody->setRestitution(m_restitution);

    m_rigidBody->setFriction(m_friction);

    m_rigidBody->setRollingFriction(m_rollingFriction);

    delete m_rigidBodyCI;
}

void AbstractBody::setMass(qreal mass){
    if(mass!=m_mass){
        m_mass=mass;
        setMassProps();
    }
}
void AbstractBody::setFallInertia(QVector3D fallInertia){
    if(m_fallInertia!=fallInertia){
       m_fallInertia=fallInertia;
       setMassProps();
    }
}

void AbstractBody::setMassProps(){
    btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
    if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
        m_shape->calculateLocalInertia(m_mass,inertia);

    m_rigidBody->setMassProps(m_mass,inertia);
    m_rigidBody->activate();
    emit worldUpdateRequired();
}

void AbstractBody::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        m_changeFlags|=MaskChanged;
    }
}

void AbstractBody::setGroup(int group){
    if(group >0 && m_group!=group){
        m_changeFlags|=GroupChanged;
    }
}
QMatrix4x4 AbstractBody::worldTransformation(){
   return static_cast<MotionState*>(m_motionState)->getWorldTransformAsQMatrix4x4();
}

void AbstractBody::setWorldTransformation(QMatrix4x4 m){   
    static_cast<MotionState*>(m_motionState)->setWorldTransform(m);
    m_rigidBody->setMotionState(m_motionState);
}


void AbstractBody::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        m_rigidBody->setRestitution(m_restitution);
    }
}
void AbstractBody::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        m_rigidBody->setRollingFriction(m_rollingFriction);
    }
}
void AbstractBody::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        m_rigidBody->setFriction(m_friction);
    }
}

void AbstractBody::applyForce(QVector3D force,QVector3D relationPosition){
    m_rigidBody->applyForce(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
}

void AbstractBody::applyImpulse(QVector3D force,QVector3D relationPosition){
    m_rigidBody->applyImpulse(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
}
void AbstractBody::clearForces(){
    m_rigidBody->clearForces();

}


}}
