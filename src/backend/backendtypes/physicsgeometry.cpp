#include "physicsgeometry.h"


#include "../physicsmanager.h"

namespace Physics {

PhysicsGeometry::PhysicsGeometry():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_attributes()
{
    m_verticesPerPatch=0;
    m_manager=Q_NULLPTR;
}

void PhysicsGeometry::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsGeometry::~PhysicsGeometry(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsGeometry::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DRender::QGeometry *geometry = static_cast<Qt3DRender::QGeometry *>(peer);
       if (geometry != Q_NULLPTR) {
           m_enabled=geometry->isEnabled();
           m_attributes.reserve(geometry->attributes().size());
           Q_FOREACH (Qt3DRender::QAbstractAttribute *attribute, geometry->attributes())
               m_attributes.push_back(attribute->id());
           m_verticesPerPatch = geometry->verticesPerPatch();
           m_dirty = true;
   }
}


void PhysicsGeometry::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
    QByteArray propertyName = propertyChange->propertyName();
    switch (e->type()) {
    case Qt3DCore::NodeAdded: {
        if (propertyName == QByteArrayLiteral("attribute")) {
            m_attributes.push_back(propertyChange->value().value<Qt3DCore::QNodeId>());
            m_dirty = true;
        }
        break;
    }
    case Qt3DCore::NodeRemoved: {
        if (propertyName == QByteArrayLiteral("attribute")) {
            m_attributes.removeOne(propertyChange->value().value<Qt3DCore::QNodeId>());
            m_dirty = true;
        }
        break;
    }
    case Qt3DCore::NodeUpdated:
        if (propertyName == QByteArrayLiteral("enabled")){
            m_enabled = propertyChange->value().value<bool>();
            m_dirty = true;
        }
        else if (propertyName == QByteArrayLiteral("verticesPerPatch")) {
            m_verticesPerPatch = propertyChange->value().value<int>();
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


Qt3DCore::QBackendNode *PhysicsGeometryFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsGeometry* geometry=new PhysicsGeometry();
    m_manager->m_resources.insert(frontend->id(),geometry);
    geometry->setFactory(factory);
    geometry->setManager(m_manager);
    geometry->setPeer(frontend);
    return geometry;
}
Qt3DCore::QBackendNode *PhysicsGeometryFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsGeometryFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}




