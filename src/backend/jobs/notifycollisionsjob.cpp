#include <backend/jobs/notifycollisionsjob.h>

#include <backend/physicsmanager.h>
#include <backend/backendtypes/physicsentity.h>
#include <backend/backendtypes/physicsbodyinfobackendnode.h>
#include <backend/backendtypes/physicstransform.h>
#include <backend/physics_entities/physicsabstractrigidbody.h>
#include <backend/physicscollision.h>

namespace Physics {

NotifyCollisionsJob::NotifyCollisionsJob(PhysicsManager* manager):
    QAspectJob()

{
    m_manager=manager;
}
void NotifyCollisionsJob::run(){
    QVector<PhysicsBodyInfoBackendNode*> bodies_to_notify;
    resetCollisions(m_manager->rootEntityId(),bodies_to_notify);

    Q_FOREACH(Physics::Collision c, m_manager->getCollisions()){
        PhysicsEntity* entity1=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body1]);
        PhysicsEntity* entity2=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body2]);
        if(!entity1->physicsBodyInfo().isNull()){
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity1->physicsBodyInfo()]);
            if(body_info->collisions().contains(c)){
                body_info->collisions().operator [](c)=1;
            }
            else {
                body_info->collisions().operator [](c)=2;

            }
        }
        if(!entity2->physicsBodyInfo().isNull()){
            /*Swap the collision bodies*/
            c.swapBodies();
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity2->physicsBodyInfo()]);
            if(body_info->collisions().contains(c)){
                body_info->collisions().operator [](c)=1;
            }
            else {
                body_info->collisions().operator [](c)=2;
            }
        }
    }

    Q_FOREACH(PhysicsBodyInfoBackendNode* b, bodies_to_notify){
        b->notifyFrontEnd("notifyCollision");
    }
}

void NotifyCollisionsJob::resetCollisions(Qt3DCore::QNodeId nodeId, QVector<PhysicsBodyInfoBackendNode*>& bodies_to_notify){
        if(nodeId.isNull()) return;
        PhysicsEntity* entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](nodeId));
        PhysicsBodyInfoBackendNode* body_info=Q_NULLPTR;
        if(!entity->physicsBodyInfo().isNull())
            body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        if(body_info){
            bodies_to_notify.append(body_info);
            body_info->resetCollisions();
        }
        for(Qt3DCore::QNodeId childId : entity->childrenIds())
            resetCollisions(childId,bodies_to_notify);

}

}


