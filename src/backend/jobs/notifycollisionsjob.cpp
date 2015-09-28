#include "notifycollisionsjob.h"

#include "../physicsmanager.h"
#include "backendtypes/physicsentity.h"
#include "backendtypes/physicsbodyinfobackendnode.h"
#include "backendtypes/physicstransform.h"

#include  "physics_entities/physicsabstractrigidbody.h"
namespace Physics {

NotifyCollisionsJob::NotifyCollisionsJob(PhysicsManager* manager):
    QAspectJob()

{
    m_manager=manager;
}
void NotifyCollisionsJob::run(){
    Q_FOREACH(PhysicsManager::Collision c, m_manager->getCollisions()){
        PhysicsEntity* entity1=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body1]);
        PhysicsEntity* entity2=static_cast<PhysicsEntity*>(m_manager->m_resources[c.body2]);
        if(!entity1->physicsBodyInfo().isNull()){
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity1->physicsBodyInfo()]);
            QVariantMap args;
            QVariant nodeId;
            nodeId.setValue(c.body2);
            args["target"]=nodeId;
            args["pointOnBody"]=c.pointOnBody1;
            args["pointOnTarget"]=c.pointOnBody2;
            args["normalOnTarget"]=c.normalBody2;//Check what the normal means
            body_info->notifyFrontEnd("notifyCollision",args);
        }
        if(!entity2->physicsBodyInfo().isNull()){
            PhysicsBodyInfoBackendNode* body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources[entity2->physicsBodyInfo()]);
            QVariantMap args;
            QVariant nodeId;
            nodeId.setValue(c.body1);
            args["target"]=nodeId;
            args["pointOnBody"]=c.pointOnBody2;
            args["pointOnTarget"]=c.pointOnBody1;
            args["normalOnTarget"]=c.normalBody2;//Check what the normal means
            body_info->notifyFrontEnd("notifyCollision",args);
        }
    }
}

}


