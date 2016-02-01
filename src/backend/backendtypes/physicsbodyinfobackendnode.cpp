#include "physicsbodyinfobackendnode.h"


#include <physicsbodyinfo.h>
#include <physicssoftbodyinfo.h>

#include "../physicsmanager.h"

namespace Physics {

PhysicsBodyInfoBackendNode::PhysicsBodyInfoBackendNode():
    Qt3DCore::QBackendNode(Qt3DCore::QBackendNode::ReadWrite),
    m_dirtyFlags(Clean),
    m_objectName(),
    m_enabled(false)
{
    m_manager=Q_NULLPTR;
}

void PhysicsBodyInfoBackendNode::setManager(PhysicsManager *manager){
        m_manager=manager;
}

PhysicsBodyInfoBackendNode::~PhysicsBodyInfoBackendNode(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsBodyInfoBackendNode::updateFromPeer(Qt3DCore::QNode *peer){
    PhysicsBodyInfo *body_info = static_cast<PhysicsBodyInfo*>(peer);
    m_objectName = peer->objectName();
    setEnabled(body_info->isEnabled());
    setFallInertia(body_info->fallInertia());
    setFriction(body_info->friction());
    setGroup(body_info->group());
    setMask(body_info->mask());
    setKinematic(body_info->kinematic());
    setMass(body_info->mass());
    setRestitution(body_info->restitution());
    setRollingFriction(body_info->rollingFriction());
    setShapeDetails(body_info->shapeDetails());
    if(body_info->inputTransform())
        setInputTransform(body_info->inputTransform()->id());

}

void PhysicsBodyInfoBackendNode::setMass(qreal mass){
    if(mass >=0 && m_mass!=mass){
        m_mass=mass;
        m_dirtyFlags.operator |=(MassChanged);
    }
}
void PhysicsBodyInfoBackendNode::setFallInertia(QVector3D fallInertia){
    if( m_fallInertia!=fallInertia){
        m_fallInertia=fallInertia;
        m_dirtyFlags.operator |=(FallInertiaChanged);
    }
}

void PhysicsBodyInfoBackendNode::setShapeDetails(QVariantMap shapeDetails){
    m_shapeDetails=shapeDetails;
    m_dirtyFlags.operator |=(ShapeDetailsChanged);
}


void PhysicsBodyInfoBackendNode::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        m_mask=mask;
        m_dirtyFlags.operator |=(MaskChanged);
    }
}

void PhysicsBodyInfoBackendNode::setGroup(int group){
    if(group >0 && m_group!=group){
        m_group=group;
        m_dirtyFlags.operator |=(GroupChanged);
    }
}
void PhysicsBodyInfoBackendNode::setKinematic(bool kinematic){
    if(m_kinematic!=kinematic){
        m_kinematic=kinematic;
        m_dirtyFlags.operator |=(KinematicChanged);
    }
}

void PhysicsBodyInfoBackendNode::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        m_dirtyFlags.operator |=(RestistutionChanged);
    }
}

void PhysicsBodyInfoBackendNode::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        m_dirtyFlags.operator |=(RollingFrictionChanged);
    }
}
void PhysicsBodyInfoBackendNode::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        m_dirtyFlags.operator |=(FrictionChanged);
    }

}

void PhysicsBodyInfoBackendNode::setInputTransform(Qt3DCore::QNodeId inputTranform){
    if(inputTranform!=m_inputTransform){
        m_inputTransform=inputTranform;
        m_dirtyFlags.operator |=(InputTransformChanged);
    }
}



void PhysicsBodyInfoBackendNode::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3DCore::NodeUpdated: {
            Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("fallInertia"))
                setFallInertia(propertyChange->value().value<QVector3D>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("friction"))
                setFriction(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("group"))
                setGroup(propertyChange->value().toInt());
            else if (propertyChange->propertyName() == QByteArrayLiteral("mask"))
                setMask(propertyChange->value().toInt());
            else if (propertyChange->propertyName() == QByteArrayLiteral("kinematic"))
                setKinematic(propertyChange->value().toBool());
            else if (propertyChange->propertyName() == QByteArrayLiteral("mass"))
                setMass(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("restitution"))
                setRestitution(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("rollingFriction"))
                setRollingFriction(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("shapeDetails"))
                setShapeDetails(propertyChange->value().value<QVariantMap>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                setEnabled(propertyChange->value().toBool());
            else if (propertyChange->propertyName() == QByteArrayLiteral("inputMatrix"))
                setInputTransform(propertyChange->value().value<Qt3DCore::QTransform*>()->id());
            break;
        }
        default:
            break;
    }
}

void PhysicsBodyInfoBackendNode::resetCollisions(){
    Q_FOREACH(Collision c, m_collisions.keys()){
        m_collisions[c]=0;
    }
}

void PhysicsBodyInfoBackendNode::setEnabled(bool val)
{
    if(m_enabled!=val){
        m_enabled=val;
        m_dirtyFlags |= (EnabledChanged);
    }
}



void PhysicsBodyInfoBackendNode::notifyFrontEnd(QString operation){
    Qt3DCore::QBackendScenePropertyChangePtr e(new Qt3DCore::QBackendScenePropertyChange(Qt3DCore::NodeUpdated, peerUuid()));
    /*if(operation=="attachPhysicsTransfrom"){
        e->setPropertyName("attachPhysicsTransfrom");
        e->setValue(true);
    }
    else */
    if(operation=="updateTransform"){
        e->setPropertyName("updateTransform");
        e->setValue(m_local_transform);
    }
    else if(operation=="notifyCollision"){
        PhysicsCollisionEventPtrList collisions_list;
        if(m_collisions.values().contains(0) || m_collisions.values().contains(2)){
            e->setPropertyName("notifyCollision");
            Q_FOREACH(Collision c, m_collisions.keys()){
                //qDebug()<<c.body1<<" "<<c.body2;
                if(m_collisions[c]==0){
                    m_collisions.remove(c);
                    continue;
                }
                PhysicsCollisionEvent* collision_event=new PhysicsCollisionEvent();
                if(m_collisions[c]==1){
                    collision_event->setIsNew(false);
                }
                else{
                    collision_event->setIsNew(true);
                }

                //if(c.body1==peerUuid()){
                    collision_event->setTarget(c.body2);
                    collision_event->setContactPointOnBody(c.pointOnBody1);
                    collision_event->setContactPointOnTarget(c.pointOnBody2);
                    collision_event->setContactPointOnBodyLocal(c.pointOnBody1Local);
                    collision_event->setContactPointOnTargetLocal(c.pointOnBody2Local);
                    collision_event->setNormalOnTarget(QVector3D());
                /*}
                else{
                    collision_event->setTarget(c.body1);
                    collision_event->setContactPointOnBody(c.pointOnBody2);
                    collision_event->setContactPointOnTarget(c.pointOnBody1);
                    collision_event->setNormalOnTarget(QVector3D());
                }*/
                PhysicsCollisionEventPtr event_ptr;
                event_ptr.reset(collision_event);
                collisions_list.append(event_ptr);

            }
            //qDebug()<<"end";
            e->setValue(QVariant::fromValue(collisions_list));
        }
        else return;
    }
    else{
        return;
    }
    // The Frontend element has to perform the action (PhysicsBodyInfo)
    e->setTargetNode(peerUuid());
    notifyObservers(e);
}




PhysicsBodyInfoBackendNodeFunctor::PhysicsBodyInfoBackendNodeFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsBodyInfoBackendNodeFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsBodyInfoBackendNode* body_info=new PhysicsBodyInfoBackendNode();
    m_manager->m_resources.insert(frontend->id(),body_info);
    body_info->setFactory(factory);
    body_info->setManager(m_manager);
    body_info->setPeer(frontend);
    return body_info;
}
Qt3DCore::QBackendNode *PhysicsBodyInfoBackendNodeFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsBodyInfoBackendNodeFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


