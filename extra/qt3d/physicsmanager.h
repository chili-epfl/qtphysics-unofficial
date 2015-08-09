#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Qt3DCore/QNodeId>
#include <QHash>
#include <Qt3DCore/QBackendNode>

namespace Physics {

class PhysicsEntity;
class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();

    QHash<Qt3D::QNodeId,PhysicsEntity*> resources(){return m_resources;}
    void setRootEntityId(Qt3D::QNodeId rootId){m_rootId=rootId;}
    Qt3D::QNodeId rootEntityId(){return m_rootId;}

signals:

public slots:

private:

    QHash<Qt3D::QNodeId,PhysicsEntity*> m_resources;
    Qt3D::QNodeId m_rootId;

};

}
#endif // PHYSICSMANAGER_H
