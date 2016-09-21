#include <backend/physicsmanager.h>
#include <backend/backendtypes/physicsentity.h>

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

    Q_FOREACH(Qt3DCore::QBackendNode* node, m_resources.values())
        delete node;

    m_Id2RigidBodies.clear();
    m_RigidBodies2Id.clear();
    delete m_physics_world;
}


void PhysicsManager::loadPhysicsFactories(){
#ifdef ANDROID
    QString pluginsPath="../lib";
#else
    QString pluginsPath = QLibraryInfo::location(QLibraryInfo::PluginsPath) + PHYSICS_FACTORIES_PATH;
#endif
    QDir physicsFactoryPluginDir(pluginsPath);
    //TODO: handle more than 1
    Q_FOREACH (QString plugin, physicsFactoryPluginDir.entryList(QDir::Files)) {
           QPluginLoader loader(physicsFactoryPluginDir.absoluteFilePath(plugin));
           loader.load();
           PhysicsFactoryInterface* factory_interface = qobject_cast<PhysicsFactoryInterface *>(loader.instance());
           if (factory_interface != Q_NULLPTR)
               m_physics_factory=factory_interface;
   }
   if(m_physics_factory==Q_NULLPTR)
       qWarning("No PhysicsFactoryInterface found");
}
/*Simply convert the collisions from the world to the format of the Physics manager.*/
QVector<Collision> PhysicsManager::getCollisions(){
    QVector<Collision> collisions;
    QVector<PhysicsAbstractDynamicsWorld::Collision> collisions_from_world=m_physics_world->getCollisions();
    qreal inv_scaleFactor=1.0/m_physics_world->scaleFactor();
    Q_FOREACH(PhysicsAbstractDynamicsWorld::Collision c,collisions_from_world){
        Collision collision;
        collision.body1=m_RigidBodies2Id[c.body1];
        collision.body2=m_RigidBodies2Id[c.body2];
        collision.normalBody2=c.normalBody2;
        collision.pointOnBody1=c.pointOnBody1*inv_scaleFactor;
        collision.pointOnBody2=c.pointOnBody2*inv_scaleFactor;
        collision.pointOnBody1Local=c.pointOnBody1Local*inv_scaleFactor;
        collision.pointOnBody2Local=c.pointOnBody2Local*inv_scaleFactor;
        collisions.append(collision);
    }
    return collisions;
}


}
