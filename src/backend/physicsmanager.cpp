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
/*Simply convert the collisions from the world to the format of the Physics manager.*/
QVector<Collision> PhysicsManager::getCollisions(){
    QVector<Collision> collisions;
    QVector<PhysicsAbstractDynamicsWorld::Collision> collisions_from_world=m_physics_world->getCollisions();
    Q_FOREACH(PhysicsAbstractDynamicsWorld::Collision c,collisions_from_world){
        Collision collision;
        collision.body1=m_RigidBodies2Id[c.body1];
        collision.body2=m_RigidBodies2Id[c.body2];
        collision.normalBody2=c.normalBody2;
        collision.pointOnBody1=c.pointOnBody1;
        collision.pointOnBody2=c.pointOnBody2;
        collisions.append(collision);
    }
    return collisions;
}


}
