#include <bodies/abstractrigidbody.h>
#include <bodies/motionstate.h>

namespace Physics {

namespace Bullet {

AbstractRigidBody::AbstractRigidBody(QObject* parent):
    PhysicsAbstractRigidBody(parent),
    m_mask(1),
    m_group(1),
    m_kinematic(false),
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

AbstractRigidBody::~AbstractRigidBody()
{
    delete m_rigidBody;
    delete m_motionState;
    delete m_shape;
}

void AbstractRigidBody::initBody(){

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

    //setKinematic(m_kinematic);

    delete m_rigidBodyCI;
}

void AbstractRigidBody::setMass(qreal mass){
    if(mass!=m_mass){
        m_mass=mass;
        setMassProps();
    }
}
void AbstractRigidBody::setFallInertia(QVector3D fallInertia){
    if(m_fallInertia!=fallInertia){
       m_fallInertia=fallInertia;
       setMassProps();
    }
}

void AbstractRigidBody::setMassProps(){
    btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
    if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
        m_shape->calculateLocalInertia(m_mass,inertia);
    m_rigidBody->setMassProps(m_mass,inertia);
    m_rigidBody->activate();
}

void AbstractRigidBody::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        m_changeFlags|=MaskChanged;
    }
}

void AbstractRigidBody::setGroup(int group){
    if(group >0 && m_group!=group){
        m_changeFlags|=GroupChanged;
    }
}

void AbstractRigidBody::setKinematic(bool kinematic){
    if(m_kinematic!=kinematic){
        m_kinematic=kinematic;
        if(m_kinematic){
            m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
            m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }
        else{
            m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
            m_rigidBody->setActivationState(ACTIVE_TAG);

        }
    }
}

QMatrix4x4 AbstractRigidBody::worldTransformation(){
       return static_cast<MotionState*>(m_motionState)->getWorldTransformAsQMatrix4x4();
}

void AbstractRigidBody::setWorldTransformation(QMatrix4x4 m){
    static_cast<MotionState*>(m_motionState)->setWorldTransform(m);
    m_rigidBody->setMotionState(m_motionState);
}


void AbstractRigidBody::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        m_rigidBody->setRestitution(m_restitution);
    }
}
void AbstractRigidBody::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        m_rigidBody->setRollingFriction(m_rollingFriction);
    }
}
void AbstractRigidBody::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        m_rigidBody->setFriction(m_friction);
    }
}

void AbstractRigidBody::applyForce(QVector3D force,QVector3D relationPosition){
    m_rigidBody->applyForce(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
}

void AbstractRigidBody::applyImpulse(QVector3D force,QVector3D relationPosition){
    m_rigidBody->applyImpulse(btVector3(force.x(),force.y(),force.z()),
                            btVector3(relationPosition.x(),relationPosition.y(),relationPosition.z()));
}
void AbstractRigidBody::clearForces(){
    m_rigidBody->clearForces();

}


}}
