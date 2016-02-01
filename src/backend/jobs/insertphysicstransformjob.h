#ifndef INSERTPHYSICSTRANSFORMJOB_H
#define INSERTPHYSICSTRANSFORMJOB_H
#include "backend_global.h"
#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>

namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT InsertPhysicsTransformJob: public Qt3DCore::QAspectJob
{

public:
    explicit InsertPhysicsTransformJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void recursive_step(Qt3DCore::QNodeId id);

     PhysicsManager* m_manager;
};


}

#endif // INSERTPHYSICSTRANSFORMJOB_H
