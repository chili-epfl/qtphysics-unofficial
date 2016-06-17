#include <frontend/physicsworldinfo.h>
#include <QVariantList>

namespace Physics {


PhysicsWorldInfo::PhysicsWorldInfo(QNode* parent):
    Qt3DCore::QComponent(parent),
    m_gravity(0, -10, 0),
    m_scaleFactor(1)
{

}

//PhysicsWorldInfo::~PhysicsWorldInfo(){
//    Qt3DCore::QNode::cleanup();
//}

void PhysicsWorldInfo::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        emit gravityChanged();
    }
}

void PhysicsWorldInfo::setScaleFactor(qreal val)
{
    if(val!=m_scaleFactor){
        m_scaleFactor=val;
        emit scaleFactorChanged();
    }
}

Qt3DCore::QNodeCreatedChangeBasePtr PhysicsWorldInfo::createNodeCreationChange() const
{
    auto creationChange = Qt3DCore::QNodeCreatedChangePtr<PhysicsWorldInfoData>::create(this);
    auto &data = creationChange->data;
    data.gravity=m_gravity;
    data.scaleFactor=m_scaleFactor;
    return creationChange;
}

//void PhysicsWorldInfo::copy(const Qt3DCore::QNode *ref){
//    Qt3DCore::QComponent::copy(ref);
//    const PhysicsWorldInfo* world_info = static_cast<const PhysicsWorldInfo*>(ref);
//    m_gravity=world_info->gravity();

//}

void PhysicsWorldInfo::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change)
{
    Qt3DCore::QPropertyUpdatedChangePtr e = qSharedPointerCast< Qt3DCore::QPropertyUpdatedChange>(change);
    if (e->type() == Qt3DCore::PropertyUpdated) {

    }
}
}


