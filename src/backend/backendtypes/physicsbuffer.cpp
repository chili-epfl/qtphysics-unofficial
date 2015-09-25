#include "physicsbuffer.h"

#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsBuffer::PhysicsBuffer():
    Qt3D::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_type(Qt3D::QBuffer::VertexBuffer),
    m_usage(Qt3D::QBuffer::StaticDraw)
{
    m_manager=Q_NULLPTR;
}

void PhysicsBuffer::setManager(PhysicsManager *manager){
    m_manager=manager;
}


PhysicsBuffer::~PhysicsBuffer(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsBuffer::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QBuffer *buffer = static_cast<Qt3D::QBuffer *>(peer);
    if (buffer != Q_NULLPTR) {
        m_type = buffer->type();
        m_usage = buffer->usage();
        m_data = buffer->data();
        m_functor = buffer->bufferFunctor();
        m_dirty = true;
    }
}

void PhysicsBuffer::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    if (e->type() == Qt3D::NodeUpdated) {
        Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
        QByteArray propertyName = propertyChange->propertyName();
        if (propertyName == QByteArrayLiteral("data")) {
            QByteArray newData = propertyChange->value().value<QByteArray>();
            m_dirty |= m_data != newData;
            m_data = newData;
        } else if (propertyName == QByteArrayLiteral("type")) {
            m_type = static_cast<Qt3D::QBuffer::BufferType>(propertyChange->value().value<int>());
            m_dirty = true;
        } else if (propertyName == QByteArrayLiteral("usage")) {
            m_usage = static_cast<Qt3D::QBuffer::UsageType>(propertyChange->value().value<int>());
            m_dirty = true;
        } else if (propertyName == QByteArrayLiteral("bufferFunctor")) {
            Qt3D::QBufferFunctorPtr newFunctor = propertyChange->value().value<Qt3D::QBufferFunctorPtr>();
            m_dirty |= !(newFunctor && m_functor && *newFunctor == *m_functor);
            m_functor = newFunctor;
        }
    }

}


PhysicsBufferFunctor::PhysicsBufferFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsBufferFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsBuffer* attribute=new PhysicsBuffer();
    m_manager->m_resources.insert(frontend->id(),attribute);
    attribute->setFactory(factory);
    attribute->setManager(m_manager);
    attribute->setPeer(frontend);
    return attribute;
}
Qt3D::QBackendNode *PhysicsBufferFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsBufferFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}







