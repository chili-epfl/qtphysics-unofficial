#include "physicscollisionevent.h"


namespace Physics {

PhysicsCollisionEvent::PhysicsCollisionEvent(QObject* parent):
    QObject(parent),
    m_target(),
    m_contactPointOnBody(0,0,0),
    m_contactPointOnTarget(0,0,0),
    m_normalOnTarget(0,0,0),
    m_isNew(true)
{

}
void PhysicsCollisionEvent::setTarget(Qt3D::QNodeId target){
    m_target=target;
}
void PhysicsCollisionEvent::setContactPointOnBody(QVector3D point){
    m_contactPointOnBody=point;
}
void PhysicsCollisionEvent::setContactPointOnTarget(QVector3D point){
    m_contactPointOnTarget=point;
}
void PhysicsCollisionEvent::setNormalOnTarget(QVector3D normal){
    m_normalOnTarget=normal;
}
void PhysicsCollisionEvent::setIsNew(bool val){
    m_isNew=val;
}





}
