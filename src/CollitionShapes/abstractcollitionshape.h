#ifndef ABSTRACTCOLLITIONSHAPE_H
#define ABSTRACTCOLLITIONSHAPE_H

#include <QObject>
#include <QQuickItem>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "motionstate.h"

namespace Bullet {
    class World;
}


namespace Bullet {


class AbstractCollitionShape : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(int mask READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(int group READ group WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(QMatrix4x4 transformation READ transformation WRITE setTransformation NOTIFY transformationChanged)
    Q_PROPERTY(QMatrix4x4 transformationFromBullet READ transformationFromBullet NOTIFY transformationFromBulletChanged)
    Q_PROPERTY(Bullet::World* world READ world WRITE setWorld)
    Q_PROPERTY(qreal mass READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(QVector3D fallInertia READ fallInertia WRITE setFallInertia NOTIFY fallInertiaChanged)

public:
    AbstractCollitionShape(QQuickItem* parent=0);
    virtual void setWorld(Bullet::World* world);
    virtual Bullet::World* world(){return m_world;}
    virtual int mask(){return m_mask;}
    virtual int group(){return m_group;}
    virtual void setMask(int mask);
    virtual void setGroup(int group);

    virtual qreal mass(){return m_mass;}
    virtual QVector3D fallInertia(){return m_fallInertia;}

    virtual void setMass(qreal mass);
    virtual void setFallInertia(QVector3D fallInertia);


    virtual QMatrix4x4 transformation(){return m_transformation;}
    virtual QMatrix4x4 transformationFromBullet();

    virtual void setTransformation(QMatrix4x4 m);

signals:
    void maskChanged(int mask);
    void groupChanged(int group);
    void transformationFromBulletChanged(QMatrix4x4 m);
    void transformationChanged(QMatrix4x4 m);
    void fallInertiaChanged(QVector3D fallInertia);
    void massChanged(qreal mass);
public slots:

protected:
    virtual void clean()=0;

    int m_mask;
    int m_group;

    qreal m_mass;
    QVector3D m_fallInertia;

    btCollisionShape* m_shape ;
    MotionState* m_motionState;
    btRigidBody::btRigidBodyConstructionInfo* m_rigidBodyCI;
    btRigidBody* m_rigidBody;
    Bullet::World* m_world;

    QMatrix4x4 m_transformation;

};

}
#endif // ABSTRACTCOLLITIONSHAPE_H
