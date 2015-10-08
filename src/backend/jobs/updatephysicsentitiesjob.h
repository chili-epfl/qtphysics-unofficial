#ifndef UpdatePhysicsEntitiesJob_H
#define UpdatePhysicsEntitiesJob_H
#include "backend_global.h"

#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>
namespace Physics {

class PhysicsManager;
class PhysicsAbstractRigidBody;
class PhysicsGeometryRenderer;
class PhysicsBodyInfoBackendNode;
class PhysicsEntity;

/*This job simply create or update the rigid bodies in the simulation and the world set up.
 * No simulation is performed, no upèdate of the objects positions in the frontend*/
class BACKENDSHARED_EXPORT UpdatePhysicsEntitiesJob : public Qt3D::QAspectJob
{
public:
    explicit UpdatePhysicsEntitiesJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void recursive_step(Qt3D::QNodeId node_id, QMatrix4x4 parent_matrix,bool forceUpdateMS);
     PhysicsAbstractRigidBody* retrievePhysicalBody(PhysicsEntity* entity,PhysicsBodyInfoBackendNode* entity_body_info,bool& isBodyNew);
     PhysicsAbstractRigidBody* createRigidBodyFromMesh(PhysicsGeometryRenderer* entity_mesh);
     PhysicsAbstractRigidBody* createRigidBodyFromShapeDetails(PhysicsBodyInfoBackendNode* entity_body_info);
     PhysicsManager* m_manager;
};

}
#endif // UpdatePhysicsEntitiesJob_H
