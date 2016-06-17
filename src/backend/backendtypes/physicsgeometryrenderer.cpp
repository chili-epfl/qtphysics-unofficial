#include <backend/backendtypes/physicsgeometryrenderer.h>

#include <backend/physicsmanager.h>
#include "Qt3DRender/private/qgeometryrenderer_p.h"

namespace Physics {

PhysicsGeometryRenderer::PhysicsGeometryRenderer():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_manager(Q_NULLPTR),
    m_geometry()
  , m_instanceCount(0)
  , m_vertexCount(0)
  , m_indexOffset(0)
  , m_firstInstance(0)
  , m_firstVertex(0)
  , m_restartIndexValue(-1)
  , m_verticesPerPatch(0)
  , m_primitiveRestartEnabled(false)
  , m_primitiveType(Qt3DRender::QGeometryRenderer::Triangles)
{

}

void PhysicsGeometryRenderer::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsGeometryRenderer::~PhysicsGeometryRenderer(){
    m_manager->m_resources.remove(peerId());
}

void PhysicsGeometryRenderer::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    Qt3DCore::QNodeCreatedChangeBase* changeData= change.data();
    m_enabled=changeData->isNodeEnabled();
    m_dirty=true;
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DRender::QGeometryRendererData>>(change);
    const auto &data = typedChange->data;
    m_geometry = data.geometryId;
    m_instanceCount = data.instanceCount;
    m_vertexCount = data.vertexCount;
    m_indexOffset = data.indexOffset;
    m_firstInstance = data.firstInstance;
    m_firstVertex = data.firstVertex;
    m_restartIndexValue = data.restartIndexValue;
    m_verticesPerPatch = data.verticesPerPatch;
    m_primitiveRestartEnabled = data.primitiveRestart;
    m_primitiveType = data.primitiveType;
    m_geometryFactory = data.geometryFactory;

}

void PhysicsGeometryRenderer::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3DCore::PropertyUpdated: {
            Qt3DCore::QPropertyUpdatedChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
            QByteArray propertyName = propertyChange->propertyName();
            if (propertyName == QByteArrayLiteral("instanceCount")) {
                m_instanceCount = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("vertexCount")) {
                m_vertexCount = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("indexOffset")) {
                m_indexOffset = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("firstInstance")) {
                m_firstInstance = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("firstVertex")) {
                m_firstVertex = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("restartIndexValue")) {
                m_restartIndexValue = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("verticesPerPatch")) {
                m_verticesPerPatch = propertyChange->value().value<int>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("primitiveRestartEnabled")) {
                m_primitiveRestartEnabled = propertyChange->value().value<bool>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("primitiveType")) {
                m_primitiveType = static_cast<Qt3DRender::QGeometryRenderer::PrimitiveType>(propertyChange->value().value<int>());
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("geometryFactory")) {
                Qt3DRender::QGeometryFactoryPtr newFunctor = propertyChange->value().value<Qt3DRender::QGeometryFactoryPtr>();
                m_dirty |= !(newFunctor && m_geometryFactory && *newFunctor == *m_geometryFactory);
                m_geometryFactory = newFunctor;
            }
            break;
        }
    case Qt3DCore::PropertyValueAdded: {
        const auto change = qSharedPointerCast<Qt3DCore::QPropertyNodeAddedChange>(e);
        if (change->propertyName() == QByteArrayLiteral("geometry")) {
            m_geometry = change->addedNodeId();
            m_dirty = true;
        }
        break;
    }
    case Qt3DCore::PropertyValueRemoved: {
        const auto change = qSharedPointerCast<Qt3DCore::QPropertyNodeAddedChange>(e);
        if (change->propertyName() == QByteArrayLiteral("geometry")) {
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

Qt3DCore::QBackendNode *PhysicsGeometryRendererFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const
{
    if(m_manager->m_resources.contains(change->subjectId())){
        return m_manager->m_resources[change->subjectId()];
    }
    else{
        PhysicsGeometryRenderer* geometry_renderer=new PhysicsGeometryRenderer();
        m_manager->m_resources.insert(change->subjectId(),geometry_renderer);
        geometry_renderer->setManager(m_manager);
        return geometry_renderer;
    }
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


