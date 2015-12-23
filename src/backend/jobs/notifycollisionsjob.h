#ifndef NOTIFYCOLLISIONSJOB_H
#define NOTIFYCOLLISIONSJOB_H
#include "backend_global.h"
#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>

namespace Physics {

class PhysicsManager;
class PhysicsBodyInfoBackendNode;
class BACKENDSHARED_EXPORT NotifyCollisionsJob: public Qt3D::QAspectJob
{
public:
    explicit NotifyCollisionsJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
    void resetCollisions(Qt3D::QNodeId nodeId,QVector<PhysicsBodyInfoBackendNode*>& bodies_to_notify);

    PhysicsManager* m_manager;
};
}

#endif // NOTIFYCOLLISIONSJOB_H
