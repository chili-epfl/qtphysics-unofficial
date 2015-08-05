#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QQuickItem>
#include <bullet/btBulletDynamicsCommon.h>
#include "simulationthread.h"

#include <QReadWriteLock>
#include <QThread>
#include <QVector3D>
#include <QHash>
#include "CollitionShapes/abstractcollitionshape.h"

namespace Bullet{


class World : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(WorldType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(qreal simulationRate READ simulationRate WRITE setSimulationRate NOTIFY simulationRateChanged)
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity NOTIFY gravityChanged)
    //Q_PROPERTY(QVariantList collitionShapes READ collitionShapes WRITE setCollitionShapes NOTIFY collitionShapesChanged)

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

    //void setCollitionShapes(QVariantList collitionShapes);
    //QVariantList collitionShapes();

    void removeRigidBody(btRigidBody* b,bool emitSignal=true);
    void addRigidBody(btRigidBody* b,int group,int mask,bool emitSignal=true);
    void removeCollitionShape(AbstractCollitionShape* b,bool emitSignal=true);
    void addCollitionShape(AbstractCollitionShape* b,bool emitSignal=true);

    void lock(){m_locker->lockForWrite();};
    void unlock(){m_locker->unlock();};

public slots:
    void start();
    void stop();
    void updateBodies();
signals:
    void typeChanged(WorldType type);
    void simulationRateChanged(qreal rate);
    void gravityChanged(QVector3D gravity);
    void collitionShapesChanged();
private:

    void init();

    WorldType m_type;
    qreal m_simulationRate;
    QVector3D m_gravity;

    QHash<QString, AbstractCollitionShape*> m_collitionShapes;

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

