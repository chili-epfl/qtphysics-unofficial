#include <backend/backendtypes/physicsattribute.h>

#include <backend/physicsmanager.h>
#include <backend/backendtypes/physicsbuffer.h>
#include "Qt3DRender/private/qattribute_p.h"
namespace Physics {

PhysicsAttribute::PhysicsAttribute():
    Qt3DCore::QBackendNode(),    
    m_bufferId(),
    m_dataType(Qt3DRender::QAttribute::Float),
    m_dataSize(1),
    m_count(0),
    m_byteStride(0),
    m_byteOffset(0),
    m_divisor(0),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_attributeType(Qt3DRender::QAttribute::VertexAttribute)
{
    m_manager=Q_NULLPTR;
}

void PhysicsAttribute::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsAttribute::~PhysicsAttribute(){
    m_manager->m_resources.remove(peerId());
}

void PhysicsAttribute::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
    case Qt3DCore::PropertyUpdated: {
        Qt3DCore::QPropertyUpdatedChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
        QByteArray propertyName = propertyChange->propertyName();
        if (propertyName == QByteArrayLiteral("enabled")){
            m_enabled = propertyChange->value().value<bool>();
        }
        else if (propertyName == QByteArrayLiteral("name")) {
            m_objectName = propertyChange->value().value<QString>();
            m_dirty = true;
        } else if (propertyName == QByteArrayLiteral("vertexBaseType")) {
            m_dataType = static_cast<Qt3DRender::QAttribute::VertexBaseType>(propertyChange->value().value<int>());
            m_dirty = true;
        } else if (propertyName == QByteArrayLiteral("vertexSize")) {
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
            m_attributeType = static_cast<Qt3DRender::QAttribute::AttributeType>(propertyChange->value().value<int>());
        }else  if (propertyName == QByteArrayLiteral("buffer")) {
            m_bufferId = propertyChange->value().value<Qt3DCore::QNodeId>();
            m_dirty = true;
        }
        break;
    }
    default:
        break;
    }

}

void PhysicsAttribute::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    Qt3DCore::QNodeCreatedChangeBase* changeData= change.data();
    m_enabled=changeData->isNodeEnabled();
    m_dirty=true;
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DRender::QAttributeData>>(change);
    const auto &data = typedChange->data;
    m_bufferId = data.bufferId;
    m_objectName = data.name;
    //m_nameId = StringToInt::lookupId(m_name);
    m_dataType = data.vertexBaseType;
    m_dataSize = data.vertexSize;
    m_count = data.count;
    m_byteStride = data.byteStride;
    m_byteOffset = data.byteOffset;
    m_divisor = data.divisor;
    m_attributeType = data.attributeType;
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

Qt3DCore::QBackendNode *PhysicsAttributeFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const
{
    if(m_manager->m_resources.contains(change->subjectId())){
        return m_manager->m_resources[change->subjectId()];
    }
    else{
        PhysicsAttribute* attribute=new PhysicsAttribute();
        m_manager->m_resources.insert(change->subjectId(),attribute);
        attribute->setManager(m_manager);
        return attribute;
    }
}

Qt3DCore::QBackendNode *PhysicsAttributeFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}

void PhysicsAttributeFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}






}





