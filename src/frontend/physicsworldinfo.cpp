#include "physicsworldinfo.h"
#include <QVariantList>
#include <Qt3DCore>
#include <Qt3DRenderer>

namespace Physics {


PhysicsWorldInfo::PhysicsWorldInfo(QNode* parent):
    Qt3D::QComponent(parent),
    m_gravity(0, -10, 0)
{

}

PhysicsWorldInfo::~PhysicsWorldInfo(){
    Qt3D::QNode::cleanup();
}

void PhysicsWorldInfo::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        emit gravityChanged(m_gravity);
    }
}

void PhysicsWorldInfo::copy(const Qt3D::QNode *ref){
    Qt3D::QComponent::copy(ref);
    const PhysicsWorldInfo* world_info = static_cast<const PhysicsWorldInfo *>(ref);
    m_gravity=world_info->gravity();

}

void PhysicsWorldInfo::sceneChangeEvent(const Qt3D::QSceneChangePtr &change)
{
    Qt3D::QScenePropertyChangePtr e = qSharedPointerCast< Qt3D::QScenePropertyChange>(change);
    if (e->type() == Qt3D::NodeUpdated) {

    }
}
}


