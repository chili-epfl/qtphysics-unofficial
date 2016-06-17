#include <backend/backendtypes/physicsbuffer.h>

#include <backend/physicsmanager.h>
#include <Qt3DRender/private/qbuffer_p.h>

namespace Physics {

PhysicsBuffer::PhysicsBuffer():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_enabled(false),
    m_dirty(false),
    m_type(),
    m_usage()
{
    m_manager=Q_NULLPTR;
}

void PhysicsBuffer::setManager(PhysicsManager *manager){
    m_manager=manager;
}


PhysicsBuffer::~PhysicsBuffer(){
    m_manager->m_resources.remove(peerId());
}

void PhysicsBuffer::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    if (e->type() == Qt3DCore::PropertyUpdated) {
        Qt3DCore::QPropertyUpdatedChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
        QByteArray propertyName = propertyChange->propertyName();
        if (propertyName == QByteArrayLiteral("enabled")){
            m_enabled = propertyChange->value().value<bool>();
        }
        else if (propertyName == QByteArrayLiteral("data")) {
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
            Qt3DRender::QBufferDataGeneratorPtr newFunctor = propertyChange->value().value<Qt3DRender::QBufferDataGeneratorPtr>();
            m_dirty |= !(newFunctor && m_functor && *newFunctor == *m_functor);
            m_functor = newFunctor;
        }
    }

}

void PhysicsBuffer::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DRender::QBufferData>>(change);
    const auto &data = typedChange->data;
    m_data = data.data;
    m_type = data.type;
    m_usage = data.usage;
    m_dirty = true;
    m_functor = data.functor;
}


PhysicsBufferFunctor::PhysicsBufferFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsBufferFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
const {
    PhysicsBuffer* attribute=new PhysicsBuffer();
    m_manager->m_resources.insert(change->subjectId(),attribute);
    attribute->setManager(m_manager);
    return attribute;
}
Qt3DCore::QBackendNode *PhysicsBufferFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsBufferFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}







