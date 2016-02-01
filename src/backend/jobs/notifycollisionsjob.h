#ifndef NOTIFYCOLLISIONSJOB_H
#define NOTIFYCOLLISIONSJOB_H
#include "qtphysicsunofficial_global.h"


namespace Physics {

class PhysicsManager;
class PhysicsBodyInfoBackendNode;
class QTPHYSICSUNOFFICIAL_EXPORT NotifyCollisionsJob: public Qt3DCore::QAspectJob
{
public:
    explicit NotifyCollisionsJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
    void resetCollisions(Qt3DCore::QNodeId nodeId,QVector<PhysicsBodyInfoBackendNode*>& bodies_to_notify);

    PhysicsManager* m_manager;
};
}

#endif // NOTIFYCOLLISIONSJOB_H
