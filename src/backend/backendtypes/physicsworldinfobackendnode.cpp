#include <backend/backendtypes/physicsworldinfobackendnode.h>


#include <frontend/physicsworldinfo.h>
#include <backend/physicsmanager.h>

namespace Physics {

PhysicsWorldInfoBackendNode::PhysicsWorldInfoBackendNode():
    Qt3DCore::QBackendNode(Qt3DCore::QBackendNode::ReadWrite),
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

void PhysicsWorldInfoBackendNode::updateFromPeer(Qt3DCore::QNode *peer){
    PhysicsWorldInfo *world_info = static_cast<PhysicsWorldInfo*>(peer);
    m_objectName = peer->objectName();
    setEnabled(world_info->isEnabled());
    setGravity(world_info->gravity());
    m_debug=world_info->debug();
}

void PhysicsWorldInfoBackendNode::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_dirtyFlags.operator |=(GravityChanged);
    }
}


void PhysicsWorldInfoBackendNode::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3DCore::NodeUpdated: {
            Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("gravity"))
                setGravity(propertyChange->value().value<QVector3D>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                setEnabled(propertyChange->value().toBool());
            else if (propertyChange->propertyName() == QByteArrayLiteral("debug"))
                m_debug = propertyChange->value().toBool();
            break;
        }
        default:
            break;
    }
}

void PhysicsWorldInfoBackendNode::notifyFrontEnd(QString operation, QVariantList args){
    Qt3DCore::QBackendScenePropertyChangePtr e(new Qt3DCore::QBackendScenePropertyChange(Qt3DCore::NodeUpdated, peerUuid()));
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

void PhysicsWorldInfoBackendNode::setEnabled(bool val)
{
    if(m_enabled!=val){
        m_enabled=val;
    }
}



PhysicsWorldInfoBackendNodeFunctor::PhysicsWorldInfoBackendNodeFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsWorldInfoBackendNodeFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsWorldInfoBackendNode* world_info=new PhysicsWorldInfoBackendNode();
    m_manager->m_resources.insert(frontend->id(),world_info);
    world_info->setFactory(factory);
    world_info->setManager(m_manager);
    world_info->setPeer(frontend);
    return world_info;
}
Qt3DCore::QBackendNode *PhysicsWorldInfoBackendNodeFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsWorldInfoBackendNodeFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}



