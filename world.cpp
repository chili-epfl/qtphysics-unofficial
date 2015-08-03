#include "world.h"

Bullet::World::World(QQuickItem *parent):
    QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);

    m_type=WorldType::DISCRETEDYNAMICSWORLD;
    m_simulationRate=60.0;
    m_gravity=QVector3D(0,-10,0);


    init();
}

Bullet::World::~World()
{
}

void Bullet::World::init(){

    m_broadphase = new btDbvtBroadphase();
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

    m_solver = new btSequentialImpulseConstraintSolver;

    switch (m_type) {
    case WorldType::DISCRETEDYNAMICSWORLD:
        m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
        break;
    case WorldType::SOFTRIGIDDYNAMICSWORLD:

        break;
    default:
        qFatal("Bullet: unknown world type");
        break;
    }

    m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));


    m_simThread=new SimulationThread(m_locker,m_dynamicsWorld,this);
    m_simThread->moveToThread(&m_workerThread);
    connect(this,SIGNAL(simulationRateChanged(qreal)),m_simThread,SLOT(setSimulationRate(qreal)));
    connect(m_simThread,SIGNAL(updated()),this,SLOT(updateBodies()));

}

void Bullet::World::setType(WorldType type){
    if(m_type!=type){
        m_type=type;
        emit typeChanged(m_type);
    }
}

void Bullet::World::setSimulationRate(qreal rate){
    if(m_simulationRate!=rate){
        m_simulationRate=rate;
        emit simulationRateChanged(m_simulationRate);
    }
}

void Bullet::World::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        m_locker->lockForWrite();
        m_dynamicsWorld->setGravity(btVector3(m_gravity.x(),m_gravity.y(),m_gravity.z()));
        m_locker->unlock();
        emit gravityChanged(m_gravity);
    }
}

void Bullet::World::start(){
    m_simThread->start();
}

void Bullet::World::stop(){
    m_simThread->stop();
}
void Bullet::World::updateBodies(){
    m_locker->lockForRead();

    m_locker->unlock();
}


void Bullet::World::setBodies(QListAbstractCollitionShapePtr bodies){
    for(AbstractCollitionShape* b: bodies)
        b->setWorld(this);

}


void Bullet::World::removeRigidBody(btRigidBody* b,bool emitSignal){
    m_locker->lockForWrite();
    m_dynamicsWorld->removeRigidBody(b);
    m_locker->unlock();
    if(emitSignal)
        emit bodiesChanged();
}
void Bullet::World::addRigidBody(btRigidBody* b,bool emitSignal){
    m_locker->lockForWrite();
    m_dynamicsWorld->addRigidBody(b);
    m_locker->unlock();
    if(emitSignal)
        emit bodiesChanged();

}
