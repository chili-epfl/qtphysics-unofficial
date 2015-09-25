#include "physicsgeometry.h"


#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsGeometry::PhysicsGeometry():
    Qt3D::QBackendNode(),
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

void PhysicsGeometry::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QGeometry *geometry = static_cast<Qt3D::QGeometry *>(peer);
       if (geometry != Q_NULLPTR) {
           m_attributes.reserve(geometry->attributes().size());
           Q_FOREACH (Qt3D::QAbstractAttribute *attribute, geometry->attributes())
               m_attributes.push_back(attribute->id());
           m_verticesPerPatch = geometry->verticesPerPatch();
           m_dirty = true;
   }
}


void PhysicsGeometry::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
    QByteArray propertyName = propertyChange->propertyName();
    switch (e->type()) {
    case Qt3D::NodeAdded: {
        if (propertyName == QByteArrayLiteral("attribute")) {
            m_attributes.push_back(propertyChange->value().value<Qt3D::QNodeId>());
            m_dirty = true;
        }
        break;
    }
    case Qt3D::NodeRemoved: {
        if (propertyName == QByteArrayLiteral("attribute")) {
            m_attributes.removeOne(propertyChange->value().value<Qt3D::QNodeId>());
            m_dirty = true;
        }
        break;
    }
    case Qt3D::NodeUpdated:
        if (propertyName == QByteArrayLiteral("verticesPerPatch")) {
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


Qt3D::QBackendNode *PhysicsGeometryFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsGeometry* geometry=new PhysicsGeometry();
    m_manager->m_resources.insert(frontend->id(),geometry);
    geometry->setFactory(factory);
    geometry->setManager(m_manager);
    geometry->setPeer(frontend);
    return geometry;
}
Qt3D::QBackendNode *PhysicsGeometryFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsGeometryFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}




