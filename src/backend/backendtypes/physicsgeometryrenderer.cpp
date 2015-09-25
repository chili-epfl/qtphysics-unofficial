#include "physicsgeometryrenderer.h"

#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsGeometryRenderer::PhysicsGeometryRenderer():
    Qt3D::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_geometry(),
    m_geometry_functor()

{
    m_manager=Q_NULLPTR;
    m_type=GENERAL;
}

void PhysicsGeometryRenderer::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsGeometryRenderer::~PhysicsGeometryRenderer(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsGeometryRenderer::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QGeometryRenderer *geometry_renderer = static_cast<Qt3D::QGeometryRenderer*>(peer);
    if(geometry_renderer->inherits("Qt3D::QCuboidMesh")){
        m_type=CUBOID;
        Qt3D::QCuboidMesh* _mesh =static_cast<Qt3D::QCuboidMesh*>(peer);
        m_x_dim=_mesh->xExtent();
        m_y_dim=_mesh->yExtent();
        m_z_dim=_mesh->zExtent();
    }
    else if (geometry_renderer->inherits("Qt3D::QSphereMesh")){
        m_type=SPHERE;
        Qt3D::QSphereMesh* _mesh =static_cast<Qt3D::QSphereMesh*>(peer);
        m_radius=_mesh->radius();
    }
    else {
        m_type=GENERAL;
    }
    m_objectName = peer->objectName();
    m_dirty=true;
    m_enabled=geometry_renderer->isEnabled();
    if (geometry_renderer->geometry() != Q_NULLPTR)
        setGeometry(geometry_renderer->geometry()->id());
    m_geometry_functor = geometry_renderer->geometryFunctor();
}

void PhysicsGeometryRenderer::setGeometry(Qt3D::QNodeId geometry)
{
    if (m_geometry != geometry) {
        m_geometry = geometry;
    }
}

void PhysicsGeometryRenderer::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3D::NodeUpdated: {
            Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("geometryFunctor")){ // Mesh with source
                m_geometry_functor= propertyChange->value().value<Qt3D::QGeometryFunctorPtr>();
                m_dirty=true;
            }
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            break;
    }
    case Qt3D::NodeAdded: {
        Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("geometry")) {
            m_geometry = propertyChange->value().value<Qt3D::QNodeId>();
            m_dirty = true;
        }
        break;
    }
    case Qt3D::NodeRemoved: {
        Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("geometry")) {
            m_geometry = Qt3D::QNodeId();
            m_dirty = true;
        }
        break;
    }
    default:
        break;
    }
}


PhysicsGeometryRendererFunctor::PhysicsGeometryRendererFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsGeometryRendererFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsGeometryRenderer* geometry_renderer=new PhysicsGeometryRenderer();
    m_manager->m_resources.insert(frontend->id(),geometry_renderer);
    geometry_renderer->setFactory(factory);
    geometry_renderer->setManager(m_manager);
    geometry_renderer->setPeer(frontend);
    return geometry_renderer;
}
Qt3D::QBackendNode *PhysicsGeometryRendererFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsGeometryRendererFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


