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

void PhysicsSoftBodyInfoBackendNode::updateFromPeer(Qt3D::QNode *peer){
    PhysicsBodyInfoBackendNode::updateFromPeer(peer);
    PhysicsSoftBodyInfo *soft_body_info = static_cast<PhysicsSoftBodyInfo*>(peer);
    setInputMesh(soft_body_info->inputMesh()->id());

}

void PhysicsSoftBodyInfoBackendNode::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    PhysicsBodyInfoBackendNode::sceneChangeEvent(e);
    switch (e->type()) {
    case Qt3D::NodeUpdated: {
        Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("inputMesh"))
            setInputMesh(propertyChange->value().value<Qt3D::QGeometryRenderer*>()->id());
        break;
    }
    default:
        break;
    }

}

void PhysicsSoftBodyInfoBackendNode::setInputMesh(Qt3D::QNodeId inputMesh){
    if(m_inputMesh!=inputMesh){
        m_inputMesh=inputMesh;
        m_dirtyMesh=true;
    }
}



PhysicsSoftBodyInfoBackendNodeFunctor::PhysicsSoftBodyInfoBackendNodeFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsSoftBodyInfoBackendNodeFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsSoftBodyInfoBackendNode* body_info=new PhysicsSoftBodyInfoBackendNode();
    m_manager->m_resources.insert(frontend->id(),body_info);
    body_info->setFactory(factory);
    body_info->setManager(m_manager);
    body_info->setPeer(frontend);
    return body_info;
}
Qt3D::QBackendNode *PhysicsSoftBodyInfoBackendNodeFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsSoftBodyInfoBackendNodeFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}

}
