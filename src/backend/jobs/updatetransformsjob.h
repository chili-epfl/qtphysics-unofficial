#ifndef UPDATETRANSFORMSJOB_H
#define UPDATETRANSFORMSJOB_H
#include <qtphysicsunofficial_global.h>


namespace Physics {

class PhysicsManager;

class QTPHYSICSUNOFFICIAL_EXPORT UpdateTransformsJob: public Qt3DCore::QAspectJob
{
public:
    explicit UpdateTransformsJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};
}

#endif // UPDATETRANSFORMSJOB_H
