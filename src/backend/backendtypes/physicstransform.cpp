#include "physicstransform.h"
#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsTransform::PhysicsTransform():
    Qt3D::QBackendNode(),
    m_dirty(false),
    m_enabled(false),
    m_transformMatrix(),
    m_objectName()

{
    m_manager=Q_NULLPTR;
}

void PhysicsTransform::setManager(PhysicsManager *manager){
        m_manager=manager;
}

PhysicsManager* PhysicsTransform::manager(){
    return m_manager;
}

PhysicsTransform::~PhysicsTransform(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsTransform::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QTransform *transform = static_cast<Qt3D::QTransform *>(peer);
    m_transformMatrix = transform->matrix();
    m_enabled = transform->isEnabled();
}

void PhysicsTransform::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    if (e->type() == Qt3D::NodeUpdated) {
            const Qt3D::QScenePropertyChangePtr &propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("matrix"))
                m_transformMatrix = propertyChange->value().value<QMatrix4x4>();
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            m_dirty=true;
    }
}


PhysicsTransformFunctor::PhysicsTransformFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsTransformFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsTransform* transform=new PhysicsTransform();
    m_manager->m_resources.insert(frontend->id(),transform);
    transform->setFactory(factory);
    transform->setManager(m_manager);
    transform->setPeer(frontend);
    return transform;
}
Qt3D::QBackendNode *PhysicsTransformFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsTransformFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


