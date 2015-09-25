#include "debugdrawjob.h"

#include "../physicsmanager.h"
#include "../backendtypes/physicsentity.h"
#include "../backendtypes/physicsworldinfobackendnode.h"

namespace Physics {


DebugDrawJob::DebugDrawJob(PhysicsManager* manager):
    QAspectJob()
{
    m_manager=manager;
}

void DebugDrawJob::run(){
    recursive_step(m_manager->rootEntityId());
}

void DebugDrawJob::recursive_step(Qt3D::QNodeId id){
    if(id.isNull()) return;
    PhysicsEntity* e= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](id));

    if(!e->physicsWorldInfo().isNull()){
        PhysicsWorldInfoBackendNode* entity_physics_world_info=static_cast<PhysicsWorldInfoBackendNode*>(m_manager->m_resources.operator [](e->physicsWorldInfo()));
        entity_physics_world_info->notifyFrontEnd("debugdraw",m_manager->m_physics_world->debugEntities());
        return;
    }

    for(Qt3D::QNodeId childId : e->childrenIds())
        recursive_step(childId);
}

}
