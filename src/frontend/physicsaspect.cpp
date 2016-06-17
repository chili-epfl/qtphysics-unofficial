#include <frontend/physicsaspect.h>
#include <backend/physicsmanager.h>

#include <backend/backendtypes/physicsentity.h>
#include <backend/backendtypes/physicsgeometryrenderer.h>
#include <backend/backendtypes/physicsgeometry.h>
#include <backend/backendtypes/physicsattribute.h>
#include <backend/backendtypes/physicstransform.h>
#include <backend/backendtypes/physicsbodyinfobackendnode.h>
#include <backend/backendtypes/physicsworldinfobackendnode.h>
#include <backend/backendtypes/physicsbuffer.h>

#include <frontend/physicsbodyinfo.h>

#include <frontend/physicsworldinfo.h>

#include <backend/jobs/debugjob.h>
#include <backend/jobs/simulatestepjob.h>
#include <backend/jobs/updatetransformsjob.h>
#include <backend/jobs/notifycollisionsjob.h>

#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QBuffer>

using namespace Qt3DCore;
QT_BEGIN_NAMESPACE
namespace Physics {

PhysicsAspect::PhysicsAspect(QObject* parent):
    Qt3DCore::QAbstractAspect(parent)
{
    m_manager=new PhysicsManager();
    registerBackendType<Qt3DCore::QEntity>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsEntityFunctor(m_manager)));
    registerBackendType<Qt3DRender::QGeometryRenderer>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsGeometryRendererFunctor(m_manager)));
    registerBackendType<Qt3DRender::QGeometry>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsGeometryFunctor(m_manager)));
    registerBackendType<Qt3DRender::QAttribute>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsAttributeFunctor(m_manager)));
    registerBackendType<Qt3DRender::QBuffer>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsBufferFunctor(m_manager)));
    registerBackendType<Qt3DCore::QTransform>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsTransformFunctor(m_manager)));
    registerBackendType<Physics::PhysicsBodyInfo>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsBodyInfoBackendNodeFunctor(m_manager)));
    registerBackendType<Physics::PhysicsWorldInfo>(Qt3DCore::QBackendNodeMapperPtr(new Physics::PhysicsWorldInfoBackendNodeFunctor(m_manager)));
    //registerBackendType<Physics::PhysicsSoftBodyInfo>(Qt3DCore::QBackendNodeFunctorPtr(new Physics::PhysicsSoftBodyInfoBackendNodeFunctor(m_manager)));

}

PhysicsAspect::~PhysicsAspect()
{
    delete m_manager;
}

QVector<Qt3DCore::QAspectJobPtr> PhysicsAspect::jobsToExecute(qint64 time){
    Q_UNUSED(time);
    QVector<Qt3DCore::QAspectJobPtr> jobs;
    if(m_manager->m_physics_factory!=Q_NULLPTR && m_manager->m_physics_world!=Q_NULLPTR){
        Qt3DCore::QAspectJobPtr insert_physics_transform, update_physics_entities, simulate_step,update_transform,notify_collisions;
        //insert_physics_transform.reset(new InsertPhysicsTransformJob(m_manager));

        update_physics_entities.reset(new UpdatePhysicsEntitiesJob(m_manager));
        simulate_step.reset(new SimulateStepJob(m_manager));
        update_transform.reset(new UpdateTransformsJob(m_manager));
        notify_collisions.reset(new NotifyCollisionsJob(m_manager));

        update_physics_entities->addDependency(insert_physics_transform);
        simulate_step->addDependency(update_physics_entities);
        update_transform->addDependency(simulate_step);
        notify_collisions->addDependency(simulate_step);


        //jobs.append(insert_physics_transform);
        jobs.append(update_physics_entities);
        jobs.append(simulate_step);
        jobs.append(update_transform);
        jobs.append(notify_collisions);

        if(m_manager->m_physics_world->debug()){

        }

        /*Qt3DCore::QAspectJobPtr debug_job;
        debug_job.reset(new DebugJob(m_manager));
        jobs.append(debug_job);*/

    }
    return jobs;

}

void PhysicsAspect::onRegistered()
{
}

void PhysicsAspect::onEngineStartup()
{
    // When this is called, the backend nodes have been created
    // so we should have a valid rootEntity
    qDebug() << Q_FUNC_INFO << m_manager->rootEntityId();
}

}

QT_END_NAMESPACE

QT3D_REGISTER_NAMESPACED_ASPECT("physics", QT_PREPEND_NAMESPACE(Physics), PhysicsAspect);
