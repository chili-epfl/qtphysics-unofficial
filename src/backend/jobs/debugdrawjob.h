#ifndef DEBUGDRAWJOB_H
#define DEBUGDRAWJOB_H


#include "backend_global.h"

#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>
namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT DebugDrawJob: public Qt3D::QAspectJob
{
public:
    DebugDrawJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void recursive_step(Qt3D::QNodeId id);
     PhysicsManager* m_manager;
};


}
#endif // DEBUGDRAWJOB_H
