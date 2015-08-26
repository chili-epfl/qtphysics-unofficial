#include "physicsentity.h"
#include "physicsbodyinfo.h"
#include "physicsworldinfo.h"

#include "../physicsmanager.h"


#include <Qt3DRenderer>
namespace Physics {

PhysicsEntity::PhysicsEntity():
    Qt3D::QBackendNode(),
    m_parentId(),
    m_objectName(),
    m_default_transform(),
    m_physics_transform(),
    m_abstractmesh(),
    m_physicsBodyInfo(),
    m_physicsWorldInfo()

{
    m_manager=Q_NULLPTR;
}

void PhysicsEntity::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsEntity::~PhysicsEntity(){
    m_manager->m_resources.remove(peerUuid());
    for (Qt3D::QNodeId id : m_childrenId){
        if(m_manager->m_resources.contains(id))
            delete m_manager->m_resources.operator [](id);
    }
}

void PhysicsEntity::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QEntity *entity = static_cast<Qt3D::QEntity*>(peer);
    Qt3D::QEntity *parentEntity = entity->parentEntity();
    m_objectName = peer->objectName();
    m_abstractmesh=Qt3D::QNodeId();
    m_physicsBodyInfo=Qt3D::QNodeId();
    m_default_transform=Qt3D::QNodeId();
    m_physics_transform=Qt3D::QNodeId();
    m_physicsWorldInfo=Qt3D::QNodeId();

    for(Qt3D::QComponent* comp : entity->components()){
        addComponent(comp);
    }
    if (parentEntity != Q_NULLPTR)
        setParentEntity(parentEntity);
}

void PhysicsEntity::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
   Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
       switch (e->type()) {
       case Qt3D::ComponentAdded: {
           Qt3D::QNodePtr nodePtr = propertyChange->value().value<Qt3D::QNodePtr>();
           Qt3D::QComponent *component = qobject_cast<Qt3D::QComponent *>(nodePtr.data());
           addComponent(component);
           break;
       }
       case Qt3D::ComponentRemoved: {
           Qt3D::QNodeId nodeId = propertyChange->value().value<Qt3D::QNodeId>();
           removeComponent(nodeId);
           break;
       }
       default:
           break;
   }
}

void PhysicsEntity::setParentEntity(Qt3D::QEntity *parent){
    if(!m_parentId.isNull() && m_manager->m_resources.contains(m_parentId)){
        PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
        parent_entity->removeChildId(peerUuid());
    }
    if(parent==Q_NULLPTR){
        m_parentId=Qt3D::QNodeId();
    }
    else{
    m_parentId=parent->id();
        if(m_manager->m_resources.contains(m_parentId)){
            PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
            parent_entity->addChildId(peerUuid());
        }
    }
}

void PhysicsEntity::addComponent(Qt3D::QComponent *component){
    if (qobject_cast<Qt3D::QTransform*>(component) != Q_NULLPTR && component->objectName().compare("@MaDeByPhYsIcS@")!=0)
        m_default_transform = component->id();
    else if (qobject_cast<Qt3D::QTransform*>(component) != Q_NULLPTR && component->objectName().compare("@MaDeByPhYsIcS@")==0)
        m_physics_transform = component->id();
    else if (qobject_cast<Qt3D::QAbstractMesh*>(component) != Q_NULLPTR)
        m_abstractmesh = component->id();
    else if (qobject_cast<PhysicsBodyInfo*>(component) != Q_NULLPTR)
        m_physicsBodyInfo = component->id();
    else if (qobject_cast<PhysicsWorldInfo*>(component) != Q_NULLPTR)
        m_physicsWorldInfo = component->id();
}

void PhysicsEntity::removeComponent(Qt3D::QNodeId componentId){
    if (m_default_transform==componentId)
        m_default_transform = Qt3D::QNodeId();
    else if (m_abstractmesh==componentId)
        m_abstractmesh = Qt3D::QNodeId();
    else if (m_physicsBodyInfo==componentId)
        m_physicsBodyInfo = Qt3D::QNodeId();
    else if(m_physics_transform==componentId)
        m_physics_transform=Qt3D::QNodeId();
    else if(m_physicsWorldInfo==componentId)
        m_physicsWorldInfo=Qt3D::QNodeId();
}

PhysicsEntity* PhysicsEntity::parent(){
    if(m_manager->m_resources.contains(m_parentId))
        return static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
    return Q_NULLPTR;
}
void PhysicsEntity::addChildId(Qt3D::QNodeId childId){
       m_childrenId.insert(childId);
}
void PhysicsEntity::removeChildId(Qt3D::QNodeId childId){
    if(m_childrenId.contains(childId))
       m_childrenId.remove(childId);
}



PhysicsEntityFunctor::PhysicsEntityFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsEntityFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsEntity* entity=new PhysicsEntity();
    m_manager->m_resources.insert(frontend->id(),entity);
    entity->setFactory(factory);
    entity->setManager(m_manager);
    entity->setPeer(frontend);
    return entity;
}
Qt3D::QBackendNode *PhysicsEntityFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsEntityFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}
