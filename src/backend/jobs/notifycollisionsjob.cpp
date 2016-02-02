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

    /*Reset Collition*/
    PhysicsEntity* entity;
    PhysicsBodyInfoBackendNode* body_info;
    Q_FOREACH(Qt3DCore::QNodeId nodeId, m_manager->m_Id2RigidBodies.keys()){
        entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](nodeId));
        body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        body_info->resetCollisions();
    }
    /*Set collitions*/
    PhysicsEntity *entity1, *entity2;
    Q_FOREACH(Physics::Collision c, m_manager->getCollisions()){
        entity1=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body1]);
        entity2=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body2]);
        body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity1->physicsBodyInfo()]);
        if(body_info->collisions().contains(c)){
            body_info->collisions().operator [](c)=1;
        }
        else {
            body_info->collisions().operator [](c)=2;

        }
        /*Swap the collision bodies*/
        c.swapBodies();
        body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity2->physicsBodyInfo()]);
        if(body_info->collisions().contains(c)){
            body_info->collisions().operator [](c)=1;
        }
        else {
            body_info->collisions().operator [](c)=2;
        }
    }
    Q_FOREACH(Qt3DCore::QNodeId nodeId, m_manager->m_Id2RigidBodies.keys()){
        entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](nodeId));
        body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        body_info->notifyFrontEnd("notifyCollision");
    }
}

}


