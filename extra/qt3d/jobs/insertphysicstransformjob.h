#ifndef INSERTPHYSICSTRANSFORMJOB_H
#define INSERTPHYSICSTRANSFORMJOB_H


#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/QNodeId>
namespace Physics {

class PhysicsManager;

class InsertPhysicsTransformJob: public Qt3D::QAspectJob
{

public:
    InsertPhysicsTransformJob(PhysicsManager* manager);
protected:
     void run() Q_DECL_OVERRIDE;
private:
     void recursive_step(Qt3D::QNodeId id);
     PhysicsManager* m_manager;
};


}

#endif // INSERTPHYSICSTRANSFORMJOB_H
