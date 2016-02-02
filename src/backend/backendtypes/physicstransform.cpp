#include <backend/backendtypes/physicstransform.h>
#include <backend/physicsmanager.h>

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
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsTransform::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DCore::QTransform *transform = static_cast<Qt3DCore::QTransform *>(peer);
    m_rotation = transform->rotation();
    m_scale = transform->scale3D();
    m_translation = transform->translation();
    updateMatrix();
    m_enabled = transform->isEnabled();
    m_dirty=true;
}

void PhysicsTransform::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    if (e->type() == Qt3DCore::NodeUpdated) {
            const Qt3DCore::QScenePropertyChangePtr &propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
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


Qt3DCore::QBackendNode *PhysicsTransformFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsTransform* transform=new PhysicsTransform();
    m_manager->m_resources.insert(frontend->id(),transform);
    transform->setFactory(factory);
    transform->setManager(m_manager);
    transform->setPeer(frontend);
    return transform;
}
Qt3DCore::QBackendNode *PhysicsTransformFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsTransformFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


