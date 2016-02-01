#include "physicsworldinfo.h"
#include <QVariantList>

namespace Physics {


PhysicsWorldInfo::PhysicsWorldInfo(QNode* parent):
    Qt3DCore::QComponent(parent),
    m_gravity(0, -10, 0)
{

}

PhysicsWorldInfo::~PhysicsWorldInfo(){
    Qt3DCore::QNode::cleanup();
}

void PhysicsWorldInfo::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        emit gravityChanged(m_gravity);
    }
}

void PhysicsWorldInfo::copy(const Qt3DCore::QNode *ref){
    Qt3DCore::QComponent::copy(ref);
    const PhysicsWorldInfo* world_info = static_cast<const PhysicsWorldInfo*>(ref);
    m_gravity=world_info->gravity();

}

void PhysicsWorldInfo::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change)
{
    Qt3DCore::QScenePropertyChangePtr e = qSharedPointerCast< Qt3DCore::QScenePropertyChange>(change);
    if (e->type() == Qt3DCore::NodeUpdated) {

    }
}
}


