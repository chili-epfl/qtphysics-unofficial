#ifndef UpdatePhysicsEntitiesJob_H
#define UpdatePhysicsEntitiesJob_H
#include "qtphysicsunofficial_global.h"
#include <QQueue>

namespace Physics {

class PhysicsManager;
class PhysicsAbstractRigidBody;
class PhysicsGeometryRenderer;
class PhysicsBodyInfoBackendNode;
class PhysicsEntity;

/*This job simply create or update the rigid bodies in the simulation and the world set up.
 * No simulation is performed, no update of the objects positions in the frontend*/
class QTPHYSICSUNOFFICIAL_EXPORT UpdatePhysicsEntitiesJob : public Qt3DCore::QAspectJob
{
public:
    explicit UpdatePhysicsEntitiesJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void recursive_step(Qt3DCore::QNodeId node_id, QMatrix4x4 parent_matrix,bool forceUpdateMS);
     PhysicsAbstractRigidBody* retrievePhysicalBody(PhysicsEntity* entity,PhysicsBodyInfoBackendNode* entity_body_info,bool& isBodyNew);
     PhysicsAbstractRigidBody* createRigidBodyFromMesh(PhysicsGeometryRenderer* entity_mesh);
     PhysicsAbstractRigidBody* createRigidBodyFromShapeDetails(PhysicsBodyInfoBackendNode* entity_body_info);
     PhysicsManager* m_manager;

     struct Visit_Data{
         Qt3DCore::QNodeId node_id;
         QMatrix4x4 parent_matrix;
         bool forceUpdateMS;
     };

     QQueue<Visit_Data> visit_queue;
};

}
#endif // UpdatePhysicsEntitiesJob_H
