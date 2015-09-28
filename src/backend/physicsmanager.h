#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "backend_global.h"
#include <Qt3DCore/QNodeId>
#include <QHash>
#include <Qt3DCore/QBackendNode>
#include "physics_entities/physicsabstractrigidbody.h"
#include "physics_entities/physicsabstractdynamicsworld.h"
#include "physics_entities/physicsfactoryinterface.h"
#include <QString>
#include <QVector3D>
namespace Physics {

const QString PHYSICS_FACTORIES_PATH = QStringLiteral("/physicsfactories");

class BACKENDSHARED_EXPORT PhysicsManager
{

public:
    struct Collision{
        Qt3D::QNodeId body1;
        Qt3D::QNodeId body2;
        QVector3D pointOnBody1;
        QVector3D pointOnBody2;
        QVector3D normalBody2;
    };

    PhysicsManager();
    ~PhysicsManager();

    void setRootEntityId(Qt3D::QNodeId rootId){m_rootId=rootId;}
    Qt3D::QNodeId rootEntityId(){return m_rootId;}
    QHash<Qt3D::QNodeId,Qt3D::QBackendNode*> m_resources;
    QHash<Qt3D::QNodeId,PhysicsAbstractRigidBody*> m_Id2RigidBodies;
    QHash<PhysicsAbstractRigidBody*,Qt3D::QNodeId> m_RigidBodies2Id;

    PhysicsAbstractDynamicsWorld* m_physics_world;
    PhysicsFactoryInterface* m_physics_factory;

    QVector<Collision> getCollisions();

signals:

public slots:

private:

    void loadPhysicsFactories();
    Qt3D::QNodeId m_rootId;



};

}
#endif // PHYSICSMANAGER_H
