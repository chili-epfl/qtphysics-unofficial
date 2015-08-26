#include "insertphysicstransformjob.h"

#include "../physicsmanager.h"
#include "../backendtypes/physicsentity.h"
#include "../backendtypes/physicsbodyinfobackendnode.h"
#include <QDebug>

namespace Physics {

InsertPhysicsTransformJob::InsertPhysicsTransformJob(PhysicsManager* manager):
    QAspectJob()
{
    m_manager=manager;
}

void InsertPhysicsTransformJob::run(){
    recursive_step(m_manager->rootEntityId());
}

void InsertPhysicsTransformJob::recursive_step(Qt3D::QNodeId id){
    if(id.isNull()) return;
    PhysicsEntity* entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](id));
    if(!entity->physicsBodyInfo().isNull() &&
            !entity->default_transform().isNull() &&
            entity->physics_transform().isNull()){
        /*Make the backend node notify the front end that a matrix should be added*/
        PhysicsBodyInfoBackendNode* b_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        b_info->notifyFrontEnd("attachPhysicsTransfrom",QVariantMap());
    }
    for(Qt3D::QNodeId childId : entity->childrenIds())
        recursive_step(childId);
}

}

