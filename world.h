#ifndef WORLD_H
#define WORLD_H

#include <QQuickItem>
#include <bullet/btBulletDynamicsCommon.h>
#include "simulationthread.h"
#include "abstractcollitionshape.h"

#include <QReadWriteLock>
#include <QThread>
#include <QVector3D>

namespace Bullet{

typedef QList<AbstractCollitionShape*> QListAbstractCollitionShapePtr;

class World : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(World)
    Q_PROPERTY(WorldType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(qreal simulationRate READ simulationRate WRITE setSimulationRate NOTIFY simulationRateChanged)
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity NOTIFY gravityChanged)
    Q_PROPERTY(QListAbstractCollitionShapePtr bodies READ bodies WRITE setBodies NOTIFY bodiesChanged)

public:
    enum WorldType{DISCRETEDYNAMICSWORLD,SOFTRIGIDDYNAMICSWORLD};

    World(QQuickItem *parent = 0);
    ~World();

    WorldType type(){return m_type;}
    void setType(WorldType type);
    qreal simulationRate(){return m_simulationRate;}
    void setSimulationRate(qreal rate);
    QVector3D gravity(){return m_gravity;}
    void setGravity(QVector3D gravity);
    //QQmlListProperty bodies(){};
    void setBodies(QListAbstractCollitionShapePtr bodies);
    QListAbstractCollitionShapePtr bodies(){return m_bodies;}

    void removeRigidBody(btRigidBody* b,bool emitSignal=true);
    void addRigidBody(btRigidBody* b,bool emitSignal=true);

public slots:
    void start();
    void stop();
    void updateBodies();
signals:
    void typeChanged(WorldType type);
    void simulationRateChanged(qreal rate);
    void gravityChanged(QVector3D gravity);
    void bodiesChanged();
private:

    void init();

    WorldType m_type;
    qreal m_simulationRate;
    QVector3D m_gravity;

    /*TODO ???*/
    QListAbstractCollitionShapePtr m_bodies;

    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDynamicsWorld* m_dynamicsWorld;

    QReadWriteLock* m_locker;
    QThread m_workerThread;
    Bullet::SimulationThread* m_simThread;
};

}

#endif // WORLD_H

