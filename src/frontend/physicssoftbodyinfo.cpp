#include "physicssoftbodyinfo.h"

namespace Physics {



PhysicsSoftBodyInfo::PhysicsSoftBodyInfo(Qt3D::QNode* parent):
    PhysicsBodyInfo(parent),
    m_inputMesh(Q_NULLPTR),
    m_outputMesh(Q_NULLPTR)
{

}

PhysicsSoftBodyInfo::~PhysicsSoftBodyInfo(){

}

void PhysicsSoftBodyInfo::copy(const Qt3D::QNode *ref){
    Qt3D::QComponent::copy(ref);
    PhysicsBodyInfo::copy(ref);
    const PhysicsSoftBodyInfo * body_info = static_cast<const PhysicsSoftBodyInfo *>(ref);

    m_inputMesh=body_info->m_inputMesh;
    m_outputMesh=body_info->m_outputMesh;

}

void PhysicsSoftBodyInfo::setInputMesh(Qt3D::QGeometryRenderer* mesh){
    if(m_inputMesh!=mesh){
        m_inputMesh=mesh;
        emit inputMeshChanged();
    }
}

}
