#include "simulationthread.h"

Bullet::SimulationThread::SimulationThread(QReadWriteLock* locker,btDynamicsWorld* dynamicsWorld,QObject* parent) :QObject(parent)
{
    m_dynamicsWorld=dynamicsWorld;
    m_locker=locker;

}

void Bullet::SimulationThread::start(){
    m_timer.setInterval(1000.0/m_simulationRate);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(update()));
}

void Bullet::SimulationThread::stop(){
    m_timer.stop();
}
void Bullet::SimulationThread::update(){
    m_locker->lockForWrite();
    m_dynamicsWorld->stepSimulation(m_simulationRate,100);
    m_locker->unlock();
    emit updated();
}
