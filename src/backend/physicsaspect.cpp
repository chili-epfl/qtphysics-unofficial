#include "physicsaspect.h"
#include "physicsmanager.h"

#include "backendtypes/physicsentity.h"
#include "backendtypes/physicsmesh.h"
#include "backendtypes/physicstransform.h"
#include "backendtypes/physicsbodyinfobackendnode.h"
#include "backendtypes/physicsworldinfobackendnode.h"

#include <physicsbodyinfo.h>
#include <physicsworldinfo.h>

#include "jobs/debugjob.h"
#include "jobs/insertphysicstransformjob.h"
#include "jobs/simulatestepjob.h"
#include "jobs/updatetransformsjob.h"

#include <Qt3DCore/qaspectfactory.h>
#include <Qt3DCore/qnodevisitor.h>
#include <Qt3DCore/qscenepropertychange.h>

#include <Qt3DRenderer/QAbstractMesh>
#include <Qt3DCore/QTransform>


QT_BEGIN_NAMESPACE
namespace Physics {

PhysicsAspect::PhysicsAspect(QObject* parent):
    Qt3D::QAbstractAspect(AspectType::AspectPhysicsAndCollision,parent)
{
    m_manager=new PhysicsManager();
    registerBackendType<Qt3D::QEntity>(Qt3D::QBackendNodeFunctorPtr(new Physics::PhysicsEntityFunctor(m_manager)));
    registerBackendType<Qt3D::QAbstractMesh>(Qt3D::QBackendNodeFunctorPtr(new Physics::PhysicsMeshFunctor(m_manager)));
    registerBackendType<Qt3D::QTransform>(Qt3D::QBackendNodeFunctorPtr(new Physics::PhysicsTransformFunctor(m_manager)));
    registerBackendType<Physics::PhysicsBodyInfo>(Qt3D::QBackendNodeFunctorPtr(new Physics::PhysicsBodyInfoBackendNodeFunctor(m_manager)));
    registerBackendType<Physics::PhysicsWorldInfo>(Qt3D::QBackendNodeFunctorPtr(new Physics::PhysicsWorldInfoBackendNodeFunctor(m_manager)));

}

QVector<Qt3D::QAspectJobPtr> PhysicsAspect::jobsToExecute(qint64 time){
    Q_UNUSED(time);
    QVector<Qt3D::QAspectJobPtr> jobs;
    if(m_manager->m_physics_factory!=Q_NULLPTR && m_manager->m_physics_world!=Q_NULLPTR){
        Qt3D::QAspectJobPtr insert_physics_transform, update_physics_entities, simulate_step,update_transform;
        insert_physics_transform.reset(new InsertPhysicsTransformJob(m_manager));
        update_physics_entities.reset(new UpdatePhysicsEntitiesJob(m_manager));
        simulate_step.reset(new SimulateStepJob(m_manager));
        update_transform.reset(new UpdateTransformsJob(m_manager));

        update_physics_entities->addDependency(insert_physics_transform);
        simulate_step->addDependency(update_physics_entities);
        update_transform->addDependency(simulate_step);

        jobs.append(insert_physics_transform);
        jobs.append(update_physics_entities);
        jobs.append(simulate_step);
        jobs.append(update_transform);

    }
    return jobs;

}

void PhysicsAspect::sceneNodeAdded(Qt3D::QSceneChangePtr &e) {
    Qt3D::QScenePropertyChangePtr propertyChange = e.staticCast<Qt3D::QScenePropertyChange>();
    Qt3D::QNodePtr nodePtr = propertyChange->value().value<Qt3D::QNodePtr>();
    Qt3D::QNode *n = nodePtr.data();
    Qt3D::QNodeVisitor visitor;
    visitor.traverse(n, this, &PhysicsAspect::visitNode, &PhysicsAspect::visitNode);
}
void PhysicsAspect::sceneNodeRemoved(Qt3D::QSceneChangePtr &e) {
    Qt3D::QScenePropertyChangePtr propertyChange = e.staticCast<Qt3D::QScenePropertyChange>();
    Qt3D::QNodePtr nodePtr = propertyChange->value().value<Qt3D::QNodePtr>();
    Qt3D::QNode *n = nodePtr.data();
    Qt3D::QAbstractAspect::clearBackendNode(n);
}

void PhysicsAspect::setRootEntity(Qt3D::QEntity *rootObject) {
    Qt3D::QNodeVisitor visitor;
    visitor.traverse(rootObject, this, &PhysicsAspect::visitNode, &PhysicsAspect::visitNode);
    m_manager->setRootEntityId(rootObject->id());
}

void PhysicsAspect::onInitialize(const QVariantMap &data) {
    Q_UNUSED(data);

}

void PhysicsAspect::onCleanup() {
    delete m_manager;
}

void PhysicsAspect::visitNode(Qt3D::QNode *node){
    Qt3D::QAbstractAspect::createBackendNode(node);
}

}

QT_END_NAMESPACE

QT3D_REGISTER_NAMESPACED_ASPECT("physics", QT_PREPEND_NAMESPACE(Physics), PhysicsAspect);
