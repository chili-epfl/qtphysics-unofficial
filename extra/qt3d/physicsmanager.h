#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Qt3DCore/QNodeId>
#include <QHash>
#include <Qt3DCore/QBackendNode>

namespace Physics {

class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();

    void setRootEntityId(Qt3D::QNodeId rootId){m_rootId=rootId;}
    Qt3D::QNodeId rootEntityId(){return m_rootId;}
    QHash<Qt3D::QNodeId,Qt3D::QBackendNode*> m_resources;

signals:

public slots:

private:

    Qt3D::QNodeId m_rootId;

};

}
#endif // PHYSICSMANAGER_H
