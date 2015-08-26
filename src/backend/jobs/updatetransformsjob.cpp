#include "updatetransformsjob.h"
#include "../physicsmanager.h"
#include "backendtypes/physicsentity.h"
#include "backendtypes/physicsbodyinfobackendnode.h"
#include "backendtypes/physicstransform.h"

#include  "physics_entities/physicsabstractrigidbody.h"
namespace Physics {

UpdateTransformsJob::UpdateTransformsJob(PhysicsManager* manager):
    QAspectJob()

{
    m_manager=manager;

}
void UpdateTransformsJob::run(){

    recursive_step(m_manager->rootEntityId(),QMatrix4x4());
}

void UpdateTransformsJob::recursive_step(Qt3D::QNodeId node_id, QMatrix4x4 parent_matrix){
    if(node_id.isNull()) return;
    QMatrix4x4 current_world_transform=parent_matrix;
    PhysicsEntity* entity=static_cast<PhysicsEntity*>(m_manager->m_resources[node_id]);
        if(m_manager->m_rigid_bodies.contains(node_id)){
        if(!entity->physicsBodyInfo().isNull()){
            /*Make the object not kinematic again*/
            PhysicsTransform* entity_default_transform=static_cast<PhysicsTransform*>(m_manager->m_resources.operator [](entity->default_transform()));
            if(entity_default_transform->isDirty()){
                entity_default_transform->setDirty(false);
            }
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity->physicsBodyInfo()]);
            PhysicsAbstractRigidBody* rigid_body=static_cast<PhysicsAbstractRigidBody*>(m_manager->m_rigid_bodies[node_id]);
            QVariantMap args;
            current_world_transform=parent_matrix*rigid_body->worldTransformation();
            args["Matrix"]=parent_matrix.inverted()*rigid_body->worldTransformation();
            body_info->notifyFrontEnd("updateTransform",args);
        }
    }
    Q_FOREACH(Qt3D::QNodeId id, entity->childrenIds()){
        recursive_step(id,current_world_transform);
    }
}

}
