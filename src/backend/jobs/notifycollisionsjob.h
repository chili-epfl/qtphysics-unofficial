#ifndef NOTIFYCOLLISIONSJOB_H
#define NOTIFYCOLLISIONSJOB_H
#include <qtphysicsunofficial_global.h>


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
    PhysicsManager* m_manager;
};
}

#endif // NOTIFYCOLLISIONSJOB_H
