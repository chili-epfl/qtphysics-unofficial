#include <backend/backendtypes/physicstransform.h>
#include <backend/physicsmanager.h>
#include "Qt3DCore/private/qtransform_p.h"

namespace Physics {

PhysicsTransform::PhysicsTransform():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_transformMatrix(),
    m_rotation()
  , m_scale(1.0f, 1.0f, 1.0f)
  , m_translation()
{
    m_manager=Q_NULLPTR;
}

void PhysicsTransform::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsTransform::~PhysicsTransform(){
    m_manager->m_resources.remove(peerId());
}

void PhysicsTransform::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    Qt3DCore::QNodeCreatedChangeBase* changeData= change.data();
    m_enabled=changeData->isNodeEnabled();
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<Qt3DCore::QTransformData>>(change);
    const auto &data = typedChange->data;
    m_rotation = data.rotation;
    m_scale = data.scale;
    m_translation = data.translation;
    updateMatrix();
    m_dirty=true;
}


void PhysicsTransform::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    if (e->type() == Qt3DCore::PropertyUpdated) {
        const Qt3DCore::QPropertyUpdatedChangePtr &propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("scale3D")) {
            m_scale = propertyChange->value().value<QVector3D>();
            updateMatrix();
        } else if (propertyChange->propertyName() == QByteArrayLiteral("rotation")) {
            m_rotation = propertyChange->value().value<QQuaternion>();
            updateMatrix();
        } else if (propertyChange->propertyName() == QByteArrayLiteral("translation")) {
            m_translation = propertyChange->value().value<QVector3D>();
            updateMatrix();
        }
        else if (propertyChange->propertyName() == QByteArrayLiteral("enabled")){
            m_enabled = propertyChange->value().value<bool>();
            m_dirty = true;
        }
    }
}

void PhysicsTransform::updateMatrix(){
    QMatrix4x4 m;
    m.translate(m_translation);
    m.rotate(m_rotation);
    m.scale(m_scale);
    m_transformMatrix = m;
    m_dirty=true;
}

PhysicsTransformFunctor::PhysicsTransformFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}

Qt3DCore::QBackendNode *PhysicsTransformFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const
{
    if(m_manager->m_resources.contains(change->subjectId())){
        return m_manager->m_resources[change->subjectId()];
    }
    else{
        PhysicsTransform* transform=new PhysicsTransform();
        m_manager->m_resources.insert(change->subjectId(),transform);
        transform->setManager(m_manager);
        return transform;
    }
}

Qt3DCore::QBackendNode *PhysicsTransformFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}

void PhysicsTransformFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}





}


