#include <backend/backendtypes/physicsgeometry.h>


#include <backend/physicsmanager.h>
#include <Qt3DCore/QNodeCreatedChange>
#include <Qt3DRender/private/qgeometry_p.h>

namespace Physics {

PhysicsGeometry::PhysicsGeometry():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_enabled(false),
    m_attributes()
{
    m_manager=Q_NULLPTR;
}

void PhysicsGeometry::setManager(PhysicsManager *manager){
    m_manager=manager;
}


PhysicsGeometry::~PhysicsGeometry(){
    m_manager->m_resources.remove(peerId());
}

void PhysicsGeometry::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DRender::QGeometryData>>(change);
    const auto &data = typedChange->data;
    m_attributes = data.attributeIds;
}

void PhysicsGeometry::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
    case Qt3DCore::PropertyValueAdded: {
        const auto change = qSharedPointerCast<Qt3DCore::QPropertyNodeAddedChange>(e);

        if (change->propertyName() == QByteArrayLiteral("attribute")) {
            m_attributes.push_back(change->addedNodeId());
        }
        break;
    }
    case Qt3DCore::PropertyValueRemoved: {
        const auto change = qSharedPointerCast<Qt3DCore::QPropertyNodeRemovedChange>(e);

        if (change->propertyName() == QByteArrayLiteral("attribute")) {
            m_attributes.removeOne(change->removedNodeId());
        }
        break;
    }
    case Qt3DCore::PropertyUpdated: {

        const auto change = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);

        if (change->propertyName() == QByteArrayLiteral("enabled")){
            m_enabled = change->value().value<bool>();
        }
        break;
    }

    default:
        break;
    }
}

PhysicsGeometryFunctor::PhysicsGeometryFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsGeometryFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
const {
    PhysicsGeometry* geometry=new PhysicsGeometry();
    m_manager->m_resources.insert(change->subjectId(),geometry);
    geometry->setManager(m_manager);
    return geometry;
}
Qt3DCore::QBackendNode *PhysicsGeometryFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsGeometryFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}




