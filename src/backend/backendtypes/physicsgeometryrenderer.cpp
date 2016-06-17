#include <backend/backendtypes/physicsgeometryrenderer.h>

#include <backend/physicsmanager.h>
#include <Qt3DRender/private/qgeometryrenderer_p.h>

namespace Physics {

PhysicsGeometryRenderer::PhysicsGeometryRenderer():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_geometry(),
    m_geometry_functor(),
    m_manager(Q_NULLPTR),
    m_instanceCount(0)
    , m_primitiveCount(0)
    , m_baseVertex(0)
    , m_baseInstance(0)
    , m_restartIndex(-1)
    , m_primitiveRestart(false)
    , m_primitiveType(Qt3DRender::QGeometryRenderer::Triangles)
{

}

void PhysicsGeometryRenderer::setManager(PhysicsManager *manager){
    m_manager=manager;
}

void PhysicsGeometryRenderer::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DRender::QGeometryRendererData>>(change);
    const auto &data = typedChange->data;
    m_geometry = data.geometryId;
    m_instanceCount = data.instanceCount;
    m_primitiveCount = data.vertexCount;
    m_baseInstance = data.firstInstance;
    m_baseVertex = data.firstVertex;
    m_restartIndex = data.restartIndexValue;
    m_primitiveRestart = data.primitiveRestart;
    m_primitiveType = data.primitiveType;
    m_verticesPerPatch = data.verticesPerPatch;
    Q_ASSERT(m_manager);
    m_geometry_functor = data.geometryFactory;

    m_dirty = true;
}


PhysicsGeometryRenderer::~PhysicsGeometryRenderer(){
    m_manager->m_resources.remove(peerId());
}

void PhysicsGeometryRenderer::setGeometry(Qt3DCore::QNodeId geometry)
{
    if (m_geometry != geometry) {
        m_geometry = geometry;
    }
}

void PhysicsGeometryRenderer::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3DCore::PropertyUpdated: {
        const Qt3DCore::QPropertyUpdatedChangePtr &propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
            QByteArray propertyName = propertyChange->propertyName();
            if (propertyName == QByteArrayLiteral("geometryFunctor")){ // Mesh with source
                m_geometry_functor = propertyChange->value().value<Qt3DRender::QGeometryFactoryPtr>();
                m_dirty=true;
            }
            else if (propertyName == QByteArrayLiteral("enabled")){
                m_enabled = propertyChange->value().value<bool>();
            }else if (propertyChange->propertyName() == QByteArrayLiteral("instanceCount")) {
                m_instanceCount = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("primitiveCount")) {
                m_primitiveCount = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("baseVertex")) {
                m_baseVertex = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("baseInstance")) {
                m_baseInstance = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("restartIndex")) {
                m_restartIndex = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("primitiveRestart")) {
                m_primitiveRestart = propertyChange->value().value<bool>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("geometry")) {
                m_geometry = propertyChange->value().value<Qt3DCore::QNodeId>();
            } else if (propertyName == QByteArrayLiteral("verticesPerPatch")) {
                m_verticesPerPatch = propertyChange->value().value<int>();
                break;
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


Qt3DCore::QBackendNode *PhysicsGeometryRendererFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
const {
    PhysicsGeometryRenderer* geometry_renderer=new PhysicsGeometryRenderer();
    m_manager->m_resources.insert(change->subjectId(), geometry_renderer);
    geometry_renderer->setManager(m_manager);
    return geometry_renderer;
}
Qt3DCore::QBackendNode *PhysicsGeometryRendererFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsGeometryRendererFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


