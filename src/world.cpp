#include "world.h"

Bullet::World::World(QQuickItem *parent):
    QQuickItem(parent)
{

    m_type=WorldType::DISCRETEDYNAMICSWORLD;
    m_simulationRate=60.0;
    m_gravity=QVector3D(0,-10,0);
    m_locker=new QReadWriteLock();

    init();
}

Bullet::World::~World()
{

    m_workerThread.quit();
    m_workerThread.wait();
    m_workerThread.deleteLater();

    for(AbstractCollitionShape* c: m_collitionShapes.values())
        delete c;

    delete m_simThread;

    delete m_dynamicsWorld;
    delete m_solver;
    delete m_collisionConfiguration;
    delete m_dispatcher;
    delete m_broadphase;
    delete m_locker;

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
    m_simThread=new SimulationThread(m_locker,m_dynamicsWorld);
    m_simThread->moveToThread(&m_workerThread);
    m_simThread->setSimulationRate(m_simulationRate);
    connect(this,SIGNAL(simulationRateChanged(qreal)),m_simThread,SLOT(setSimulationRate(qreal)));
    connect(m_simThread,SIGNAL(updated()),this,SLOT(updateBodies()));
    m_workerThread.start();
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
        m_simThread->setSimulationRate(m_simulationRate);
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

/*
QVariantList Bullet::World::collitionShapes(){
    QVariantList output;
    for(QString key: m_collitionShapes.keys()){
        output.append(qVariantFromValue((void *) m_collitionShapes[key]));
    }
    return output;
}

void Bullet::World::setCollitionShapes(QVariantList collitionShapes){
    for(QVariant e: collitionShapes){
       Bullet::AbstractCollitionShape c=  e.value<Bullet::AbstractCollitionShape>();
       /*qDebug()<<"D:"<<c;
       qDebug()<<"D:"<<e;
       c->setWorld(this);
       //m_collitionShapes[key]=c;
    }
    emit collitionShapesChanged();
}
*/
void Bullet::World::removeCollitionShape(AbstractCollitionShape* c,bool emitSignal){
    m_collitionShapes.remove(c->objectName());
    if(emitSignal)
        emit collitionShapesChanged();
}
void Bullet::World::addCollitionShape(AbstractCollitionShape* c,bool emitSignal){
   m_collitionShapes[c->objectName()]=c;
    if(emitSignal)
        emit collitionShapesChanged();

}

void Bullet::World::removeRigidBody(btRigidBody* b,bool emitSignal){
    m_locker->lockForWrite();
    m_dynamicsWorld->removeRigidBody(b);
    m_locker->unlock();
    if(emitSignal)
        emit collitionShapesChanged();
}
void Bullet::World::addRigidBody(btRigidBody* b,int group,int mask,bool emitSignal){
    m_locker->lockForWrite();
    m_dynamicsWorld->addRigidBody(b,group,mask);
    m_locker->unlock();
    if(emitSignal)
        emit collitionShapesChanged();

}
