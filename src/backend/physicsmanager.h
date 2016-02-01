#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "qtphysicsunofficial_global.h"
#include <QHash>

#include "physics_entities/physicsabstractrigidbody.h"
#include "physics_entities/physicsabstractsoftbody.h"
#include "physics_entities/physicsabstractdynamicsworld.h"
#include "physics_entities/physicsfactoryinterface.h"
#include <QString>
#include <QVector3D>
#include "physicscollision.h"

namespace Physics {

const QString PHYSICS_FACTORIES_PATH = QStringLiteral("/physicsfactories");

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsManager
{

public:

    PhysicsManager();
    ~PhysicsManager();

    void setRootEntityId(Qt3DCore::QNodeId rootId){m_rootId=rootId;}
    Qt3DCore::QNodeId rootEntityId(){return m_rootId;}

    QHash<Qt3DCore::QNodeId,Qt3DCore::QBackendNode*> m_resources;

    QHash<Qt3DCore::QNodeId,PhysicsAbstractRigidBody*> m_Id2RigidBodies;
    QHash<PhysicsAbstractRigidBody*,Qt3DCore::QNodeId> m_RigidBodies2Id;

    QHash<Qt3DCore::QNodeId,PhysicsAbstractSoftBody*> m_Id2SoftBodies;
    QHash<PhysicsAbstractSoftBody*,Qt3DCore::QNodeId> m_SoftBodies2Id;

    QSet<Qt3DCore::QNodeId> garbage;

    PhysicsAbstractDynamicsWorld* m_physics_world;

    PhysicsFactoryInterface* m_physics_factory;

    QVector<Collision> getCollisions();

signals:

public slots:

private:
    void loadPhysicsFactories();
    Qt3DCore::QNodeId m_rootId;

};



}
#endif // PHYSICSMANAGER_H
