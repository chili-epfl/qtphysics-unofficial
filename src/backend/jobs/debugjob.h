#ifndef DEBUGJOB_H
#define DEBUGJOB_H
#include "backend_global.h"

namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT DebugJob: public Qt3DCore::QAspectJob
{

public:
    DebugJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void print(Qt3DCore::QNodeId id);
     PhysicsManager* m_manager;
};


}

#endif // DEBUGJOB_H
