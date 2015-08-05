#ifndef SIMULATIONTHREAD_H
#define SIMULATIONTHREAD_H

#include <QObject>
#include <QReadWriteLock>
#include <QTimer>

#include <bullet/BulletDynamics/btBulletDynamicsCommon.h>

namespace Bullet {


class SimulationThread: public QObject
{
    Q_OBJECT

public:
    SimulationThread(QReadWriteLock* locker,btDynamicsWorld* dynamicsWorld, QObject* parent=0);
    ~SimulationThread();
public slots:
    void start();
    void stop();
    void update();
    void setSimulationRate(qreal simulationRate ){m_simulationRate=simulationRate; m_timer.setInterval(1000.0/m_simulationRate);}
signals:
    void updated();
private:
    qreal m_simulationRate;
    btDynamicsWorld* m_dynamicsWorld;
    QReadWriteLock* m_locker;
    QTimer m_timer;

};



}
#endif // SIMULATIONTHREAD_H
