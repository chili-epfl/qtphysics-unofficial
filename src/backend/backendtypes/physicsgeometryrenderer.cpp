#include "physicsgeometryrenderer.h"

#include "../physicsmanager.h"

namespace Physics {

PhysicsGeometryRenderer::PhysicsGeometryRenderer():
    Qt3DCore::QBackendNode(),
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

void PhysicsGeometryRenderer::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DRender::QGeometryRenderer *geometry_renderer = static_cast<Qt3DRender::QGeometryRenderer*>(peer);
    if(geometry_renderer->inherits("Qt3DRender::QCuboidMesh")){
        m_type=CUBOID;
        Qt3DRender::QCuboidMesh* _mesh =static_cast<Qt3DRender::QCuboidMesh*>(peer);
        m_x_dim=_mesh->xExtent();
        m_y_dim=_mesh->yExtent();
        m_z_dim=_mesh->zExtent();
    }
    else if (geometry_renderer->inherits("Qt3DRender::QSphereMesh")){
        m_type=SPHERE;
        Qt3DRender::QSphereMesh* _mesh =static_cast<Qt3DRender::QSphereMesh*>(peer);
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

void PhysicsGeometryRenderer::setGeometry(Qt3DCore::QNodeId geometry)
{
    if (m_geometry != geometry) {
        m_geometry = geometry;
    }
}

void PhysicsGeometryRenderer::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3DCore::NodeUpdated: {
            Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("geometryFunctor")){ // Mesh with source
                m_geometry_functor= propertyChange->value().value<Qt3DRender::QGeometryFunctorPtr>();
                m_dirty=true;
            }
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            break;
    }
    case Qt3DCore::NodeAdded: {
        Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("geometry")) {
            m_geometry = propertyChange->value().value<Qt3DCore::QNodeId>();
            m_dirty = true;
        }
        break;
    }
    case Qt3DCore::NodeRemoved: {
        Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("geometry")) {
            m_geometry = Qt3DCore::QNodeId();
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


Qt3DCore::QBackendNode *PhysicsGeometryRendererFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsGeometryRenderer* geometry_renderer=new PhysicsGeometryRenderer();
    m_manager->m_resources.insert(frontend->id(),geometry_renderer);
    geometry_renderer->setFactory(factory);
    geometry_renderer->setManager(m_manager);
    geometry_renderer->setPeer(frontend);
    return geometry_renderer;
}
Qt3DCore::QBackendNode *PhysicsGeometryRendererFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsGeometryRendererFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


