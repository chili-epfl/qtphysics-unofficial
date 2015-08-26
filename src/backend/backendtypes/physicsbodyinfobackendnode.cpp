#include "physicsbodyinfobackendnode.h"


#include <physicsbodyinfo.h>
#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsBodyInfoBackendNode::PhysicsBodyInfoBackendNode():
    Qt3D::QBackendNode(Qt3D::QBackendNode::ReadWrite),
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

void PhysicsBodyInfoBackendNode::updateFromPeer(Qt3D::QNode *peer){
    PhysicsBodyInfo *body_info = static_cast<PhysicsBodyInfo*>(peer);
    m_objectName = peer->objectName();
    m_enabled=body_info->isEnabled();
    setFallInertia(body_info->fallInertia());
    setFriction(body_info->friction());
    setGroup(body_info->group());
    setMask(body_info->mask());
    setMass(body_info->mass());
    setRestitution(body_info->restitution());
    setRollingFriction(body_info->rollingFriction());
    setShapeDetails(body_info->shapeDetails());
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



void PhysicsBodyInfoBackendNode::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3D::NodeUpdated: {
            Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("fallInertia"))
                setFallInertia(propertyChange->value().value<QVector3D>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("friction"))
                setFriction(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("group"))
                setGroup(propertyChange->value().toInt());
            else if (propertyChange->propertyName() == QByteArrayLiteral("mask"))
                setMask(propertyChange->value().toInt());
            else if (propertyChange->propertyName() == QByteArrayLiteral("mass"))
                setMass(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("restitution"))
                setRestitution(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("rollingFriction"))
                setRollingFriction(propertyChange->value().toReal());
            else if (propertyChange->propertyName() == QByteArrayLiteral("shapeDetails"))
                setShapeDetails(propertyChange->value().value<QVariantMap>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            break;
        }
        default:
            break;
    }
}

void PhysicsBodyInfoBackendNode::notifyFrontEnd(QString operation, QVariantMap args){
    Qt3D::QBackendScenePropertyChangePtr e(new Qt3D::QBackendScenePropertyChange(Qt3D::NodeUpdated, peerUuid()));
    if(operation=="attachPhysicsTransfrom"){
        e->setPropertyName("attachPhysicsTransfrom");
        e->setValue(true);
    }
    else if(operation=="updateTransform"){
        e->setPropertyName("updateTransform");
        e->setValue(args["Matrix"]);
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


Qt3D::QBackendNode *PhysicsBodyInfoBackendNodeFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsBodyInfoBackendNode* body_info=new PhysicsBodyInfoBackendNode();
    m_manager->m_resources.insert(frontend->id(),body_info);
    body_info->setFactory(factory);
    body_info->setManager(m_manager);
    body_info->setPeer(frontend);
    return body_info;
}
Qt3D::QBackendNode *PhysicsBodyInfoBackendNodeFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsBodyInfoBackendNodeFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


