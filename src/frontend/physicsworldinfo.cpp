#include "physicsworldinfo.h"

namespace Physics {


PhysicsWorldInfo::PhysicsWorldInfo(QNode* parent):
    Qt3D::QComponent(parent),
    m_gravity(0, -10, 0)
{

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

}
