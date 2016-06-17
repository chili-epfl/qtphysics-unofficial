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
    m_scaleFactor=1.0;
    m_manager=Q_NULLPTR;
}

void PhysicsWorldInfoBackendNode::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsWorldInfoBackendNode::~PhysicsWorldInfoBackendNode(){
    m_manager->m_resources.remove(peerId());
}


void PhysicsWorldInfoBackendNode::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_dirtyFlags.operator |=(GravityChanged);
    }
}

void PhysicsWorldInfoBackendNode::setScaleFactor(qreal val)
{
    if(m_scaleFactor!=val){
        m_scaleFactor=val;
        m_dirtyFlags.operator |=(ScaleFactorChanged);
    }
}


void PhysicsWorldInfoBackendNode::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e){
    switch (e->type()) {
    case Qt3DCore::PropertyUpdated: {
        const Qt3DCore::QPropertyUpdatedChangePtr &propertyChange = qSharedPointerCast<Qt3DCore::QPropertyUpdatedChange>(e);
        if (propertyChange->propertyName() == QByteArrayLiteral("gravity"))
            setGravity(propertyChange->value().value<QVector3D>());
        else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
            setEnabled(propertyChange->value().toBool());
        else if (propertyChange->propertyName() == QByteArrayLiteral("debug"))
            m_debug = propertyChange->value().toBool();
        else if (propertyChange->propertyName() == QByteArrayLiteral("scaleFactor"))
            setScaleFactor( propertyChange->value().toReal());
        break;
    }
    default:
        break;
    }
}

void PhysicsWorldInfoBackendNode::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{

    Qt3DCore::QNodeCreatedChangeBase* changeData= change.data();
    m_enabled=changeData->isNodeEnabled();
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<PhysicsWorldInfoData>>(change);
    const auto &data = typedChange->data;
    setGravity(data.gravity);
    setScaleFactor(data.scaleFactor);
}

void PhysicsWorldInfoBackendNode::notifyFrontEnd(QString operation, QVariantList args){
//    Qt3DCore::QBackendScenePropertyChangePtr e(new Qt3DCore::QBackendScenePropertyChange(Qt3DCore::NodeUpdated, peerUuid()));
//    /*if(operation=="attachPhysicsTransfrom"){
//        e->setPropertyName("attachPhysicsTransfrom");
//        e->setValue(true);
//    }
//    else */
//    if(operation=="debugdraw"){
//        e->setPropertyName("debugdraw");
//        e->setValue(args);
//    }
//    else{
//        return;
//    }
//    e->setTargetNode(peerUuid());
//    notifyObservers(e);
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

Qt3DCore::QBackendNode *PhysicsWorldInfoBackendNodeFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const
{
    if(m_manager->m_resources.contains(change->subjectId())){
        return m_manager->m_resources[change->subjectId()];
    }
    else{
        PhysicsWorldInfoBackendNode* world_info=new PhysicsWorldInfoBackendNode();
        m_manager->m_resources.insert(change->subjectId(),world_info);
        world_info->setManager(m_manager);
        return world_info;
    }
}

Qt3DCore::QBackendNode *PhysicsWorldInfoBackendNodeFunctor::get(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}

void PhysicsWorldInfoBackendNodeFunctor::destroy(Qt3DCore::QNodeId id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}



