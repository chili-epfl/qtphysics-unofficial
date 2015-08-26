#include "physicsmanager.h"
#include "backendtypes/physicsentity.h"

namespace Physics {


PhysicsManager::PhysicsManager():
    m_rootId()
{
    m_physics_world=Q_NULLPTR;
    m_physics_factory=Q_NULLPTR;
    loadPhysicsFactories();
    if(m_physics_factory){
        m_physics_world=m_physics_factory->create_dynamics_world();
    }
}

PhysicsManager::~PhysicsManager()
{
    QHash<Qt3D::QNodeId, Qt3D::QBackendNode*>::iterator i;
    for (i = m_resources.begin(); i != m_resources.end(); ++i)
        delete i.value();
}


void PhysicsManager::loadPhysicsFactories(){
    QString pluginsPath = QLibraryInfo::location(QLibraryInfo::PluginsPath) + PHYSICS_FACTORIES_PATH;
    QDir physicsFactoryPluginDir(pluginsPath);
    //TODO: handle more than 1
    Q_FOREACH (QString plugin, physicsFactoryPluginDir.entryList(QDir::Files)) {
           QPluginLoader loader(physicsFactoryPluginDir.absoluteFilePath(plugin));
           loader.load();
           m_physics_factory = qobject_cast<PhysicsFactoryInterface *>(loader.instance());
           if (m_physics_factory == Q_NULLPTR)
               qWarning() << "Failed to load physics factory plugin ";
   }
}
}
