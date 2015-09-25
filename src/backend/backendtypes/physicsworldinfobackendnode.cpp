#include "physicsworldinfobackendnode.h"


#include <physicsworldinfo.h>
#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsWorldInfoBackendNode::PhysicsWorldInfoBackendNode():
    Qt3D::QBackendNode(Qt3D::QBackendNode::ReadWrite),
    m_dirtyFlags(Clean),
    m_objectName(),
    m_enabled(false),
    m_debug(false)
{
    m_manager=Q_NULLPTR;
}

void PhysicsWorldInfoBackendNode::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsWorldInfoBackendNode::~PhysicsWorldInfoBackendNode(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsWorldInfoBackendNode::updateFromPeer(Qt3D::QNode *peer){
    PhysicsWorldInfo *world_info = static_cast<PhysicsWorldInfo*>(peer);
    m_objectName = peer->objectName();
    m_enabled=world_info->isEnabled();
    setGravity(world_info->gravity());
    m_debug=world_info->debug();
}

void PhysicsWorldInfoBackendNode::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_dirtyFlags.operator |=(GravityChanged);
    }
}


void PhysicsWorldInfoBackendNode::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3D::NodeUpdated: {
            Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("gravity"))
                setGravity(propertyChange->value().value<QVector3D>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            else if (propertyChange->propertyName() == QByteArrayLiteral("debug"))
                m_debug = propertyChange->value().toBool();
            break;
        }
        default:
            break;
    }
}

void PhysicsWorldInfoBackendNode::notifyFrontEnd(QString operation, QVariantList args){
    Qt3D::QBackendScenePropertyChangePtr e(new Qt3D::QBackendScenePropertyChange(Qt3D::NodeUpdated, peerUuid()));
    /*if(operation=="attachPhysicsTransfrom"){
        e->setPropertyName("attachPhysicsTransfrom");
        e->setValue(true);
    }
    else */
    if(operation=="debugdraw"){
        e->setPropertyName("debugdraw");
        e->setValue(args);
    }
    else{
        return;
    }
    e->setTargetNode(peerUuid());
    notifyObservers(e);
}



PhysicsWorldInfoBackendNodeFunctor::PhysicsWorldInfoBackendNodeFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsWorldInfoBackendNodeFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsWorldInfoBackendNode* world_info=new PhysicsWorldInfoBackendNode();
    m_manager->m_resources.insert(frontend->id(),world_info);
    world_info->setFactory(factory);
    world_info->setManager(m_manager);
    world_info->setPeer(frontend);
    return world_info;
}
Qt3D::QBackendNode *PhysicsWorldInfoBackendNodeFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsWorldInfoBackendNodeFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}



