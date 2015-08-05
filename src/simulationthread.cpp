#include "simulationthread.h"
#include <QDebug>
Bullet::SimulationThread::SimulationThread(QReadWriteLock* locker,btDynamicsWorld* dynamicsWorld,QObject* parent) :QObject(parent)
{
    m_dynamicsWorld=dynamicsWorld;
    m_locker=locker;
    m_simulationRate=60;

}
Bullet::SimulationThread::~SimulationThread()
{
    m_timer.stop();
}

void Bullet::SimulationThread::start(){
    m_timer.setInterval(1000.0/m_simulationRate);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(update()));
    m_timer.start();
}

void Bullet::SimulationThread::stop(){
    m_timer.stop();
}
void Bullet::SimulationThread::update(){
    m_locker->lockForWrite();
    m_dynamicsWorld->stepSimulation(1.0f/m_simulationRate,100);
    m_locker->unlock();
    emit updated();
}
