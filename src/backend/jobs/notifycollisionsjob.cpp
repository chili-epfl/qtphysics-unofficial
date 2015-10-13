#include "notifycollisionsjob.h"

#include "../physicsmanager.h"
#include "backendtypes/physicsentity.h"
#include "backendtypes/physicsbodyinfobackendnode.h"
#include "backendtypes/physicstransform.h"
#include "physics_entities/physicsabstractrigidbody.h"
#include "physicscollition.h"

namespace Physics {

NotifyCollisionsJob::NotifyCollisionsJob(PhysicsManager* manager):
    QAspectJob()

{
    m_manager=manager;
}
void NotifyCollisionsJob::run(){

    QVector<PhysicsBodyInfoBackendNode*> bodies_to_notify;
    resetCollitions(m_manager->rootEntityId(),bodies_to_notify);

    Q_FOREACH(Physics::Collision c, m_manager->getCollisions()){
        PhysicsEntity* entity1=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body1]);
        PhysicsEntity* entity2=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body2]);
        if(!entity1->physicsBodyInfo().isNull()){
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity1->physicsBodyInfo()]);
            if(body_info->collitions().contains(c)){
                body_info->collitions().operator [](c)=1;
            }
            else {
                body_info->collitions().operator [](c)=2;
            }
        }
        if(!entity2->physicsBodyInfo().isNull()){
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity2->physicsBodyInfo()]);
            if(body_info->collitions().contains(c)){
                body_info->collitions().operator [](c)=1;
            }
            else {
                body_info->collitions().operator [](c)=2;
            }
        }
    }
    Q_FOREACH(PhysicsBodyInfoBackendNode* b, bodies_to_notify){
        b->notifyFrontEnd("notifyCollision");
    }
}

void NotifyCollisionsJob::resetCollitions(Qt3D::QNodeId nodeId, QVector<PhysicsBodyInfoBackendNode*>& bodies_to_notify){
        if(nodeId.isNull()) return;
        PhysicsEntity* entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](nodeId));
        PhysicsBodyInfoBackendNode* body_info=Q_NULLPTR;
        if(!entity->physicsBodyInfo().isNull())
            body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        if(body_info){
            bodies_to_notify.append(body_info);
            body_info->resetCollitions();
        }
        for(Qt3D::QNodeId childId : entity->childrenIds())
            resetCollitions(childId,bodies_to_notify);

}

}


