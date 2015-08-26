#ifndef UPDATETRANSFORMSJOB_H
#define UPDATETRANSFORMSJOB_H
#include "backend_global.h"
#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>

namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT UpdateTransformsJob: public Qt3D::QAspectJob
{
public:
    explicit UpdateTransformsJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
    void recursive_step(Qt3D::QNodeId node_id, QMatrix4x4 parent_matrix);
    PhysicsManager* m_manager;
};
}

#endif // UPDATETRANSFORMSJOB_H
