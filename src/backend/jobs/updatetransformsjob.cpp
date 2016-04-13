#include <backend/jobs/updatetransformsjob.h>
#include <backend/physicsmanager.h>
#include <backend/backendtypes/physicsentity.h>
#include <backend/backendtypes/physicsbodyinfobackendnode.h>
#include <backend/backendtypes/physicstransform.h>
#include  <backend/physics_entities/physicsabstractrigidbody.h>

#include <QPair>

namespace Physics {

UpdateTransformsJob::UpdateTransformsJob(PhysicsManager* manager):
    QAspectJob()

{
    m_manager=manager;

}
void UpdateTransformsJob::run(){
    QQueue<QPair<Qt3DCore::QNodeId,QMatrix4x4> > nodes_to_visit;
    QPair<Qt3DCore::QNodeId,QMatrix4x4> current_node(m_manager->rootEntityId(),QMatrix4x4());
    nodes_to_visit.enqueue(current_node);
    PhysicsEntity* entity;
    QMatrix4x4 current_world_transform,global_transform;
    QVector4D translation;
    PhysicsTransform* transform;
    PhysicsBodyInfoBackendNode* body_info;
    PhysicsAbstractRigidBody* rigid_body;
    QPair<Qt3DCore::QNodeId,QMatrix4x4> childNode;
    qreal inv_scaleFactor=1.0/m_manager->m_physics_world->scaleFactor();
    while(!nodes_to_visit.isEmpty()){
        current_node=nodes_to_visit.dequeue();
        current_world_transform=current_node.second;
        entity=static_cast<PhysicsEntity*>(m_manager->m_resources[current_node.first]);
        if(!entity->transform().isNull() && m_manager->m_resources.contains(entity->transform())){
            transform=static_cast<PhysicsTransform*>(m_manager->m_resources[entity->transform()]);
            current_world_transform=current_world_transform*transform->transformMatrix();
        }
        if(m_manager->m_Id2RigidBodies.contains(current_node.first)){
                body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity->physicsBodyInfo()]);
                rigid_body=static_cast<PhysicsAbstractRigidBody*>(m_manager->m_Id2RigidBodies[current_node.first]);

                global_transform=rigid_body->worldTransformation();
                translation=global_transform.column(3);
                translation=translation*inv_scaleFactor;
                translation.setW(1);
                global_transform.setColumn(3,translation);

                current_world_transform=global_transform;
                /*If the object is not statics (or kinematic) then update the position*/
                //if(rigid_body->mass()!=0){
                body_info->setLocalTransform(current_node.second.inverted()*global_transform);
                body_info->notifyFrontEnd("updateTransform");
                //}
        }
        Q_FOREACH(Qt3DCore::QNodeId id, entity->childrenIds()){
            childNode=QPair<Qt3DCore::QNodeId,QMatrix4x4>(id,current_world_transform);
            nodes_to_visit.enqueue(childNode);
        }
    }
}


}
