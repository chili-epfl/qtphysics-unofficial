#include <backend/backendtypes/physicstransform.h>
#include <backend/physicsmanager.h>

namespace Physics {

PhysicsTransform::PhysicsTransform():
    Qt3DCore::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_transformMatrix()
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
    m_transformMatrix = transform->matrix();
    m_enabled = transform->isEnabled();
    m_dirty=true;
}

void PhysicsTransform::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    if (e->type() == Qt3DCore::NodeUpdated) {
            const Qt3DCore::QScenePropertyChangePtr &propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("matrix")){
                m_transformMatrix = propertyChange->value().value<QMatrix4x4>();
                m_dirty=true;
            }
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled")){
                m_enabled = propertyChange->value().value<bool>();
                m_dirty = true;
            }
    }
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


