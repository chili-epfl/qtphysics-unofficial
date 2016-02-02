#include <backend/backendtypes/physicsentity.h>
#include <frontend/physicsbodyinfo.h>
#include <frontend/physicsworldinfo.h>

#include <backend/physicsmanager.h>

namespace Physics {

PhysicsEntity::PhysicsEntity():
    Qt3DCore::QBackendNode(),
    m_parentId(),
    m_enabled(false),
    m_objectName(),
    m_transform(),
    m_geometry_renderer(),
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
    for (Qt3DCore::QNodeId id : m_childrenId){
        if(m_manager->m_resources.contains(id)){
            Physics::PhysicsEntity* child=static_cast<Physics::PhysicsEntity*>(m_manager->m_resources.operator [](id));
            child->setParentEntity(Q_NULLPTR);
        }
    }
    if(this->parent()){
        this->parent()->removeChildId(peerUuid());
    }
    m_manager->garbage.insert(peerUuid());
}

void PhysicsEntity::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DCore::QEntity *entity = static_cast<Qt3DCore::QEntity*>(peer);
    Qt3DCore::QEntity *parentEntity = entity->parentEntity();
    m_objectName = peer->objectName();
    m_geometry_renderer=Qt3DCore::QNodeId();
    m_physicsBodyInfo=Qt3DCore::QNodeId();
    m_transform=Qt3DCore::QNodeId();
    m_physicsWorldInfo=Qt3DCore::QNodeId();
    m_enabled=entity->isEnabled();
    for(Qt3DCore::QComponent* comp : entity->components()){
        addComponent(comp);
    }
    if (parentEntity != Q_NULLPTR)
        setParentEntity(parentEntity);
}

void PhysicsEntity::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
   Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
       switch (e->type()) {
       case Qt3DCore::ComponentAdded: {
           Qt3DCore::QNodePtr nodePtr = propertyChange->value().value<Qt3DCore::QNodePtr>();
           Qt3DCore::QComponent *component = qobject_cast<Qt3DCore::QComponent *>(nodePtr.data());
           addComponent(component);
           break;
       }
       case Qt3DCore::NodeUpdated: {
              if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                  m_enabled = propertyChange->value().value<bool>();
              break;
       }
       case Qt3DCore::ComponentRemoved: {
           Qt3DCore::QNodeId nodeId = propertyChange->value().value<Qt3DCore::QNodeId>();
           removeComponent(nodeId);
           break;
       }
       default:
           break;
   }
}

void PhysicsEntity::setParentEntity(Qt3DCore::QEntity *parent){
    if(!m_parentId.isNull() && m_manager->m_resources.contains(m_parentId)){
        PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
        parent_entity->removeChildId(peerUuid());
    }
    if(parent==Q_NULLPTR){
        m_parentId=Qt3DCore::QNodeId();
    }
    else{
    m_parentId=parent->id();
        if(m_manager->m_resources.contains(m_parentId)){
            PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
            parent_entity->addChildId(peerUuid());
        }
    }
}

void PhysicsEntity::addComponent(Qt3DCore::QComponent *component){
    if (qobject_cast<Qt3DCore::QTransform*>(component) != Q_NULLPTR)
        m_transform = component->id();
    else if (qobject_cast<Qt3DRender::QGeometryRenderer*>(component) != Q_NULLPTR)
        m_geometry_renderer = component->id();
    else if (qobject_cast<PhysicsBodyInfo*>(component) != Q_NULLPTR)
        m_physicsBodyInfo = component->id();
    else if (qobject_cast<PhysicsWorldInfo*>(component) != Q_NULLPTR)
        m_physicsWorldInfo = component->id();
}

void PhysicsEntity::removeComponent(Qt3DCore::QNodeId componentId){
    if (m_transform==componentId)
        m_transform = Qt3DCore::QNodeId();
    else if (m_geometry_renderer==componentId)
        m_geometry_renderer = Qt3DCore::QNodeId();
    else if (m_physicsBodyInfo==componentId)
        m_physicsBodyInfo = Qt3DCore::QNodeId();
     else if(m_physicsWorldInfo==componentId)
        m_physicsWorldInfo=Qt3DCore::QNodeId();
}

PhysicsEntity* PhysicsEntity::parent(){
    if(m_manager->m_resources.contains(m_parentId))
        return static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
    return Q_NULLPTR;
}

void PhysicsEntity::addChildId(Qt3DCore::QNodeId childId){
       m_childrenId.insert(childId);
}

void PhysicsEntity::removeChildId(Qt3DCore::QNodeId childId){
    if(m_childrenId.contains(childId))
       m_childrenId.remove(childId);
}

PhysicsEntityFunctor::PhysicsEntityFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsEntityFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsEntity* entity=new PhysicsEntity();
    m_manager->m_resources.insert(frontend->id(),entity);
    entity->setFactory(factory);
    entity->setManager(m_manager);
    entity->setPeer(frontend);
    return entity;
}
Qt3DCore::QBackendNode *PhysicsEntityFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsEntityFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}
