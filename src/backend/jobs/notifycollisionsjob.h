#ifndef NOTIFYCOLLISIONSJOB_H
#define NOTIFYCOLLISIONSJOB_H
#include "backend_global.h"
#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>

namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT NotifyCollisionsJob: public Qt3D::QAspectJob
{
public:
    explicit NotifyCollisionsJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};
}

#endif // NOTIFYCOLLISIONSJOB_H
