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
    QString pluginsPath = QLibraryInfo::location(QLibraryInfo::PluginsPath) + PHYSICS_FACTORIES_PATH;
    QDir physicsFactoryPluginDir(pluginsPath);
    //TODO: handle more than 1
    Q_FOREACH (QString plugin, physicsFactoryPluginDir.entryList(QDir::Files)) {
        qDebug()<<"Loading:"<<plugin;
        QPluginLoader loader(physicsFactoryPluginDir.absoluteFilePath(plugin));
        loader.load();
        m_physics_factory = qobject_cast<PhysicsFactoryInterface *>(loader.instance());
        if (m_physics_factory == Q_NULLPTR)
            qWarning() << "Failed to load physics factory plugin ";
        else{
            qDebug()<< "Loaded: " << plugin;
            return;
        }
    }
    QStringList libraryPaths=QCoreApplication::libraryPaths();
    Q_FOREACH(QString libraryPath, libraryPaths){
        physicsFactoryPluginDir.setPath(libraryPath);
        Q_FOREACH (QString plugin, physicsFactoryPluginDir.entryList(QDir::Files)) {
            qDebug()<<"Loading:"<<plugin;
            QPluginLoader loader(physicsFactoryPluginDir.absoluteFilePath(plugin));
            loader.load();
            m_physics_factory = qobject_cast<PhysicsFactoryInterface *>(loader.instance());
            if (m_physics_factory == Q_NULLPTR)
                qWarning() << "Failed to load physics factory plugin ";
            else{
                qDebug()<< "Loaded: " << plugin;
                return;
            }
        }
    }
    if(m_physics_factory==NULL)
        qWarning() << "Failed to load physics factory plugin ";

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
