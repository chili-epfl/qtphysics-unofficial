#include "physicsattribute.h"

#include "../physicsmanager.h"
#include "physicsbuffer.h"

namespace Physics {

PhysicsAttribute::PhysicsAttribute():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_bufferId(),
    m_dataType(Qt3DRender::QAbstractAttribute::Float),
    m_dataSize(1),
    m_count(0),
    m_byteStride(0),
    m_byteOffset(0),
    m_divisor(0),
    m_attributeType(Qt3DRender::QAbstractAttribute::VertexAttribute)
{
    m_manager=Q_NULLPTR;
}

void PhysicsAttribute::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsAttribute::~PhysicsAttribute(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsAttribute::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DRender::QAttribute *attribute = static_cast<Qt3DRender::QAttribute *>(peer);
        if (attribute) {
            m_dataType = attribute->dataType();
            m_dataSize = attribute->dataSize();
            m_count = attribute->count();
            m_byteOffset = attribute->byteOffset();
            m_byteStride = attribute->byteStride();
            m_divisor = attribute->divisor();
            m_attributeType = attribute->attributeType();
            m_objectName = attribute->name();
            if (attribute->buffer())
                m_bufferId = attribute->buffer()->id();
            m_dirty = true;
    }
}
void PhysicsAttribute::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
        QByteArray propertyName = propertyChange->propertyName();
        switch (e->type()) {
        case Qt3DCore::NodeUpdated: {
            if (propertyName == QByteArrayLiteral("name")) {
                m_objectName = propertyChange->value().value<QString>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("dataType")) {
                m_dataType = static_cast<Qt3DRender::QAbstractAttribute::DataType>(propertyChange->value().value<int>());
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("dataSize")) {
                m_dataSize = propertyChange->value().value<uint>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("count")) {
                m_count = propertyChange->value().value<uint>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("byteStride")) {
                m_byteStride = propertyChange->value().value<uint>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("byteOffset")) {
                m_byteOffset = propertyChange->value().value<uint>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("divisor")) {
                m_divisor = propertyChange->value().value<uint>();
                m_dirty = true;
            } else if (propertyName == QByteArrayLiteral("attributeType")) {
                m_attributeType = static_cast<Qt3DRender::QAbstractAttribute::AttributeType>(propertyChange->value().value<int>());
                m_dirty = true;
            }
            break;
        }
        case Qt3DCore::NodeAdded: {
            if (propertyName == QByteArrayLiteral("buffer")) {
                m_bufferId = propertyChange->value().value<Qt3DCore::QNodeId>();
                m_dirty = true;
            }
            break;
        }
        case Qt3DCore::NodeRemoved: {
            if (propertyName == QByteArrayLiteral("buffer")) {
                m_bufferId = Qt3DCore::QNodeId();
                m_dirty = true;
            }
            break;
        }
        default:
            break;
    }

}

/*A copy of what is in the frontend*/
QVector<QVector3D> PhysicsAttribute::asVector3D() const{
    QVector<QVector3D> result;
    if(m_bufferId.isNull() || !m_manager->m_resources.contains(m_bufferId)){
        qDebug()<<"BufferId is null";
        return result;
    }
    QByteArray buffer;
    PhysicsBuffer* buffer_node=static_cast<PhysicsBuffer*>(m_manager->m_resources.operator [](m_bufferId));
    if(buffer_node->bufferFunctor().isNull()){
        buffer=buffer_node->data();
    }
    else{
        buffer=buffer_node->bufferFunctor().data()->operator ()();
    }

    const char *rawBuffer = buffer.constData();
    rawBuffer += m_byteOffset;
    const float* fptr;
    int stride;
    switch (m_dataType) {
    case Qt3DRender::QAttribute::Float:
        stride = sizeof(float) * m_dataSize;
        break;
    default:
        qDebug()<< "can't convert" << m_dataType << "x" << m_dataSize << "to QVector3D";
        return result;
    }
    if (m_byteStride != 0)
        stride = m_byteStride;

    result.resize(m_count);
    for (uint c = 0; c < m_count; ++c) {
        QVector3D v;
        fptr = reinterpret_cast<const float*>(rawBuffer);
        for (uint i = 0, m = qMin(m_dataSize, 3U); i < m; ++i)
            v[i] = fptr[i];
        result[c] = v;
        rawBuffer += stride;
    }
    return result;
}



PhysicsAttributeFunctor::PhysicsAttributeFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsAttributeFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsAttribute* attribute=new PhysicsAttribute();
    m_manager->m_resources.insert(frontend->id(),attribute);
    attribute->setFactory(factory);
    attribute->setManager(m_manager);
    attribute->setPeer(frontend);
    return attribute;
}
Qt3DCore::QBackendNode *PhysicsAttributeFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsAttributeFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}





