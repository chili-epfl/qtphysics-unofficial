#include <backend/backendtypes/physicsentity.h>
#include <frontend/physicsbodyinfo.h>
#include <frontend/physicsworldinfo.h>

#include <backend/physicsmanager.h>
#include "Qt3DCore/private/qentity_p.h"
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
    if(!m_parentId.isNull() && m_manager->m_resources.contains(m_parentId)){
        PhysicsEntity* parent=static_cast<PhysicsEntity*>(m_manager->m_resources[m_parentId]);
        parent->removeChildId(peerId());
    }
    if(m_manager->m_Id2RigidBodies.contains(peerId())){
        PhysicsAbstractRigidBody* body =m_manager->m_Id2RigidBodies[peerId()];
        m_manager->m_Id2RigidBodies.remove(peerId());
        m_manager->m_RigidBodies2Id.remove(body);
        m_manager->m_physics_world->removeRigidBody(body);
        delete body;
    }
}

void PhysicsEntity::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change){
    Qt3DCore::QNodeCreatedChangeBase* changeData= change.data();
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DCore::QEntityData>>(change);
    const auto &data = typedChange->data;
    m_objectName = QString();
    m_geometry_renderer=Qt3DCore::QNodeId();
    m_physicsBodyInfo=Qt3DCore::QNodeId();
    m_transform=Qt3DCore::QNodeId();
    m_physicsWorldInfo=Qt3DCore::QNodeId();
    m_enabled=changeData->isNodeEnabled();

    if (!changeData->parentId().isNull())
        setParentEntity(changeData->parentId());
    for (const auto &idAndType : qAsConst(data.componentIdsAndTypes))
        addComponent(idAndType);

}

void PhysicsEntity::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
       switch (e->type()) {
       case Qt3DCore::ComponentAdded: {
           Qt3DCore::QComponentAddedChangePtr change = qSharedPointerCast<Qt3DCore::QComponentAddedChange>(e);
           const auto componentIdAndType = Qt3DCore::QNodeIdTypePair(change->componentId(), change->componentMetaObject());
           addComponent(componentIdAndType);
           break;
       }
       case Qt3DCore::PropertyUpdated: {
           Qt3DCore::QPropertyUpdatedChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
           if (propertyChange->propertyName() == QByteArrayLiteral("enabled")){
                  m_enabled = propertyChange->value().value<bool>();
              }
              else if (propertyChange->propertyName() == QByteArrayLiteral("objectName")){
                  m_objectName = propertyChange->value().value<QString>();
              }
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
   Qt3DCore::QBackendNode::sceneChangeEvent(e);
}

void PhysicsEntity::setParentEntity(Qt3DCore::QNodeId parentID){
    if(!m_parentId.isNull() && m_manager->m_resources.contains(m_parentId)){
        PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
        parent_entity->removeChildId(peerId());
    }
    if(parentID.isNull()){
        m_parentId=Qt3DCore::QNodeId();
    }
    else{   
        m_parentId=parentID;
        if(m_manager->m_resources.contains(m_parentId)){
            PhysicsEntity* parent_entity = static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](m_parentId));
            parent_entity->addChildId(peerId());
        }
        else{
            /*I hope the id will be set by the backnodemapper...*/
            PhysicsEntity* parent_entity=new PhysicsEntity();
            parent_entity->setManager(m_manager);
            m_manager->m_resources.insert(m_parentId,parent_entity);
            parent_entity->addChildId(peerId());
        }
    }
}

void PhysicsEntity::addComponent(Qt3DCore::QNodeIdTypePair idAndType){
    const auto type = idAndType.type;
    const auto id = idAndType.id;
    if (type->inherits(&Qt3DCore::QTransform::staticMetaObject)){
        m_transform = id;
    }
    else if (type->inherits(&Qt3DRender::QGeometryRenderer::staticMetaObject)){
        m_geometry_renderer = id;
    }
    else if (type->inherits(&PhysicsBodyInfo::staticMetaObject)){
        m_physicsBodyInfo = id;
    }
    else if (type->inherits(&PhysicsWorldInfo::staticMetaObject)){
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


    if(m_manager->m_resources.contains(change->subjectId())){
        return m_manager->m_resources[change->subjectId()];
    }
    else{
        PhysicsEntity* entity=new PhysicsEntity();
        m_manager->m_resources.insert(change->subjectId(),entity);
        entity->setManager(m_manager);
        return entity;
    }
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
