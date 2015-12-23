#include "physicsbuffer.h"

#include "../physicsmanager.h"

namespace Physics {

PhysicsBuffer::PhysicsBuffer():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_type(Qt3DRender::QBuffer::VertexBuffer),
    m_usage(Qt3DRender::QBuffer::StaticDraw)
{
    m_manager=Q_NULLPTR;
}

void PhysicsBuffer::setManager(PhysicsManager *manager){
    m_manager=manager;
}


PhysicsBuffer::~PhysicsBuffer(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsBuffer::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DRender::QBuffer *buffer = static_cast<Qt3DRender::QBuffer *>(peer);
    if (buffer != Q_NULLPTR) {
        m_type = buffer->type();
        m_usage = buffer->usage();
        m_data = buffer->data();
        m_functor = buffer->bufferFunctor();
        m_dirty = true;
    }
}

void PhysicsBuffer::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    if (e->type() == Qt3DCore::NodeUpdated) {
        Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
        QByteArray propertyName = propertyChange->propertyName();
        if (propertyName == QByteArrayLiteral("data")) {
            QByteArray newData = propertyChange->value().value<QByteArray>();
            m_dirty |= m_data != newData;
            m_data = newData;
        } else if (propertyName == QByteArrayLiteral("type")) {
            m_type = static_cast<Qt3DRender::QBuffer::BufferType>(propertyChange->value().value<int>());
            m_dirty = true;
        } else if (propertyName == QByteArrayLiteral("usage")) {
            m_usage = static_cast<Qt3DRender::QBuffer::UsageType>(propertyChange->value().value<int>());
            m_dirty = true;
        } else if (propertyName == QByteArrayLiteral("bufferFunctor")) {
            Qt3DRender::QBufferFunctorPtr newFunctor = propertyChange->value().value<Qt3DRender::QBufferFunctorPtr>();
            m_dirty |= !(newFunctor && m_functor && *newFunctor == *m_functor);
            m_functor = newFunctor;
        }
    }

}


PhysicsBufferFunctor::PhysicsBufferFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsBufferFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsBuffer* attribute=new PhysicsBuffer();
    m_manager->m_resources.insert(frontend->id(),attribute);
    attribute->setFactory(factory);
    attribute->setManager(m_manager);
    attribute->setPeer(frontend);
    return attribute;
}
Qt3DCore::QBackendNode *PhysicsBufferFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsBufferFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}







