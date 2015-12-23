#include "physicssoftbodyinfo.h"

namespace Physics {



PhysicsSoftBodyInfo::PhysicsSoftBodyInfo(Qt3DCore::QNode* parent):
    PhysicsBodyInfo(parent),
    m_inputMesh(Q_NULLPTR),
    m_outputMesh(Q_NULLPTR)
{

}

PhysicsSoftBodyInfo::~PhysicsSoftBodyInfo(){

}

void PhysicsSoftBodyInfo::copy(const Qt3DCore::QNode *ref){
    Qt3DCore::QComponent::copy(ref);
    PhysicsBodyInfo::copy(ref);
    const PhysicsSoftBodyInfo * body_info = static_cast<const PhysicsSoftBodyInfo *>(ref);

    m_inputMesh=body_info->m_inputMesh;
    m_outputMesh=body_info->m_outputMesh;

}

void PhysicsSoftBodyInfo::setInputMesh(Qt3DRender::QGeometryRenderer* mesh){
    if(m_inputMesh!=mesh){
        m_inputMesh=mesh;
        emit inputMeshChanged();
    }
}

}
