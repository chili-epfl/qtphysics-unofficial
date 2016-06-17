#include <backend/backendtypes/physicsentity.h>
#include <frontend/physicsbodyinfo.h>
#include <frontend/physicsworldinfo.h>

#include <backend/physicsmanager.h>
#include <Qt3DCore/private/qentity_p.h>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QComponentAddedChange>
#include <Qt3DCore/QComponentRemovedChange>

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
    m_manager->m_resources.remove(peerId());
    for (Qt3DCore::QNodeId id : m_childrenId){
        if(m_manager->m_resources.contains(id)){
            Physics::PhysicsEntity* child=static_cast<Physics::PhysicsEntity*>(m_manager->m_resources.operator [](id));
            child->setParentEntity(Qt3DCore::QNodeId());
        }
    }
    if(this->parent()){
        this->parent()->removeChildId(peerId());
    }
    if(m_manager->m_Id2RigidBodies.contains(peerId())){
        PhysicsAbstractRigidBody* body =m_manager->m_Id2RigidBodies[peerId()];
        m_manager->m_Id2RigidBodies.remove(peerId());
        m_manager->m_RigidBodies2Id.remove(body);
        m_manager->m_physics_world->removeRigidBody(body);
        delete body;
    }
}

void PhysicsEntity::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DCore::QEntityData>>(change);
    const auto &data = typedChange->data;

    m_geometry_renderer=Qt3DCore::QNodeId();
    m_physicsBodyInfo=Qt3DCore::QNodeId();
    m_transform=Qt3DCore::QNodeId();
    m_physicsWorldInfo=Qt3DCore::QNodeId();
    for (const Qt3DCore::QNodeIdTypePair &idAndType : qAsConst(data.componentIdsAndTypes))
        addComponent(idAndType.type, idAndType.id);
    const Qt3DCore::QNodeId parentEntityId = data.parentEntityId;
    if (parentEntityId)
        setParentEntity(parentEntityId);

}

void PhysicsEntity::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
    case Qt3DCore::ComponentAdded: {
        Qt3DCore::QComponentAddedChangePtr change = qSharedPointerCast<Qt3DCore::QComponentAddedChange>(e);
        addComponent(change->componentMetaObject(), change->componentId());
        break;
    }
    case Qt3DCore::ComponentRemoved: {
        Qt3DCore::QComponentRemovedChangePtr change = qSharedPointerCast<Qt3DCore::QComponentRemovedChange>(e);
        removeComponent(change->componentId());
        break;
    }
    default:
        break;
    }
    QBackendNode::sceneChangeEvent(e);
}

void PhysicsEntity::setParentEntity(Qt3DCore::QNodeId id){
    if(!m_parentId.isNull() && m_manager->m_resources.contains(m_parentId)){
        PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
        parent_entity->removeChildId(peerId());
    }
    m_parentId= id;

    if(m_manager->m_resources.contains(m_parentId)){
        PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
        parent_entity->addChildId(peerId());
    }
}

void PhysicsEntity::addComponent(const QMetaObject *obj, Qt3DCore::QNodeId id){
    if (obj->inherits(&Qt3DCore::QTransform::staticMetaObject)){
        m_transform = id;
    }
    else if (obj->inherits(&Qt3DRender::QGeometryRenderer::staticMetaObject)){
        m_geometry_renderer = id;
    }
    else if (obj->inherits(&PhysicsBodyInfo::staticMetaObject)){
        m_physicsBodyInfo = id;
    }
    else if (obj->inherits(&PhysicsWorldInfo::staticMetaObject)){
        m_physicsWorldInfo = id;
    }
}

void PhysicsEntity::removeComponent(Qt3DCore::QNodeId componentId){
    if (m_transform==componentId){
        m_transform = Qt3DCore::QNodeId();
    }
    else if (m_geometry_renderer==componentId){
        m_geometry_renderer = Qt3DCore::QNodeId();
    }
    else if (m_physicsBodyInfo==componentId){
        m_physicsBodyInfo = Qt3DCore::QNodeId();
    }
    else if(m_physicsWorldInfo==componentId){
        m_physicsWorldInfo=Qt3DCore::QNodeId();
    }
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


Qt3DCore::QBackendNode *PhysicsEntityFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
const {
    PhysicsEntity* entity=new PhysicsEntity();

    if (!m_manager->rootEntityId())
        m_manager->setRootEntityId(change->subjectId());

    m_manager->m_resources.insert(change->subjectId(),entity);
    entity->setManager(m_manager);
    return entity;
}
Qt3DCore::QBackendNode *PhysicsEntityFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsEntityFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}
