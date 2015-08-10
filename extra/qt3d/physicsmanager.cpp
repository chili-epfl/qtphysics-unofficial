#include "physicsmanager.h"
#include "physicsentity.h"

namespace Physics {


PhysicsManager::PhysicsManager():
    m_rootId()
{

}

PhysicsManager::~PhysicsManager()
{
    QHash<Qt3D::QNodeId, Qt3D::QBackendNode*>::iterator i;
    for (i = m_resources.begin(); i != m_resources.end(); ++i)
        delete i.value();
}



}
