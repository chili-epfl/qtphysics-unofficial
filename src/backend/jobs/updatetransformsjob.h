#ifndef UPDATETRANSFORMSJOB_H
#define UPDATETRANSFORMSJOB_H
#include "backend_global.h"


namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT UpdateTransformsJob: public Qt3DCore::QAspectJob
{
public:
    explicit UpdateTransformsJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
    void recursive_step(Qt3DCore::QNodeId node_id, QMatrix4x4 parent_matrix);
    PhysicsManager* m_manager;
};
}

#endif // UPDATETRANSFORMSJOB_H
