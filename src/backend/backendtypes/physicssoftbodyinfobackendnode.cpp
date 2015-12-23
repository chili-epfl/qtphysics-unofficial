#include "physicssoftbodyinfobackendnode.h"
#include "physicsmanager.h"

namespace Physics {



PhysicsSoftBodyInfoBackendNode::PhysicsSoftBodyInfoBackendNode():
    PhysicsBodyInfoBackendNode(),
    m_inputMesh()
{

}
PhysicsSoftBodyInfoBackendNode::~PhysicsSoftBodyInfoBackendNode(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsSoftBodyInfoBackendNode::updateFromPeer(Qt3DCore::QNode *peer){
    PhysicsBodyInfoBackendNode::updateFromPeer(peer);
    PhysicsSoftBodyInfo *soft_body_info = static_cast<PhysicsSoftBodyInfo*>(peer);
    setInputMesh(soft_body_info->inputMesh()->id());

}

void PhysicsSoftBodyInfoBackendNode::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    PhysicsBodyInfoBackendNode::sceneChangeEvent(e);
    switch (e->type()) {
    case Qt3DCore::NodeUpdated: {
        Qt3DCore::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3DCore::QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("inputMesh"))
            setInputMesh(propertyChange->value().value<Qt3DRender::QGeometryRenderer*>()->id());
        break;
    }
    default:
        break;
    }

}

void PhysicsSoftBodyInfoBackendNode::setInputMesh(Qt3DCore::QNodeId inputMesh){
    if(m_inputMesh!=inputMesh){
        m_inputMesh=inputMesh;
        m_dirtyMesh=true;
    }
}



PhysicsSoftBodyInfoBackendNodeFunctor::PhysicsSoftBodyInfoBackendNodeFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3DCore::QBackendNode *PhysicsSoftBodyInfoBackendNodeFunctor::create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory)
const {
    PhysicsSoftBodyInfoBackendNode* body_info=new PhysicsSoftBodyInfoBackendNode();
    m_manager->m_resources.insert(frontend->id(),body_info);
    body_info->setFactory(factory);
    body_info->setManager(m_manager);
    body_info->setPeer(frontend);
    return body_info;
}
Qt3DCore::QBackendNode *PhysicsSoftBodyInfoBackendNodeFunctor::get(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsSoftBodyInfoBackendNodeFunctor::destroy(const Qt3DCore::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}

}
