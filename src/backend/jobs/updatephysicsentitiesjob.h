#ifndef UpdatePhysicsEntitiesJob_H
#define UpdatePhysicsEntitiesJob_H
#include <qtphysicsunofficial_global.h>
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
     void iterative_step(Qt3DCore::QNodeId node_id, QMatrix4x4 parent_matrix,bool forceUpdateMS);
     bool isDefiningBody(PhysicsEntity* entity);
     bool isRequiringShapeUpdate(PhysicsGeometryRenderer* entity_geometry_renderer);
     void removeNotEnabledSubtrees(Qt3DCore::QNodeId rootId);

     PhysicsAbstractRigidBody* createRigidBodyFromMesh(PhysicsGeometryRenderer* entity_mesh);

     PhysicsManager* m_manager;

     struct Visit_Data{
         Qt3DCore::QNodeId node_id;
         QMatrix4x4 parent_matrix;
         bool forceUpdateMS;
         void set(Qt3DCore::QNodeId id,QMatrix4x4 mat,bool fU){
             node_id=id;
             parent_matrix=mat;
             forceUpdateMS=fU;
         }
     };

     QQueue<Visit_Data> m_visit_queue;
};

}
#endif // UpdatePhysicsEntitiesJob_H
