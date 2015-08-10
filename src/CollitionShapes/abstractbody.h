#ifndef ABSTRACTBODY_H
#define ABSTRACTBODY_H

#include <QObject>
#include <QQuickItem>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "motionstate.h"

namespace Bullet {
    class World;
}


namespace Bullet {


class AbstractBody : public QQuickItem {
    Q_OBJECT

    Q_PROPERTY(int mask READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(int group READ group WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(bool kinematic READ kinematic WRITE setKinematic NOTIFY kinematicChanged)

    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal rollingFriction READ rollingFriction WRITE setRollingFriction NOTIFY rollingFrictionChanged)
    Q_PROPERTY(qreal mass READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(QVector3D fallInertia READ fallInertia WRITE setFallInertia NOTIFY fallInertiaChanged)

    Q_PROPERTY(QMatrix4x4 worldTransformation READ worldTransformation WRITE setWorldTransformation NOTIFY worldTransformationChanged)
    Q_PROPERTY(Bullet::World* world READ world WRITE setWorld)

public:
    AbstractBody(QQuickItem* parent=0);

    virtual void setWorld(Bullet::World* world);
    virtual Bullet::World* world(){return m_world;}

    virtual int mask(){return m_mask;}
    virtual int group(){return m_group;}

    virtual void setMask(int mask);
    virtual void setGroup(int group);

    virtual bool kinematic(){return m_kinematic;}
    virtual void setKinematic(bool kinematic);

    virtual QMatrix4x4 worldTransformation(){return m_worldTransformation;}
    virtual void setWorldTransformation(QMatrix4x4 m);


    virtual qreal restitution(){return m_restitution;}
    virtual qreal rollingFriction(){return m_rollingFriction;}
    virtual qreal friction(){return m_friction;}
    virtual qreal mass(){return m_mass;}
    virtual QVector3D fallInertia(){return m_fallInertia;}

    virtual void setRestitution(qreal restitution);
    virtual void setRollingFriction(qreal rollingFriction);
    virtual void setFriction(qreal friction);
    virtual void setMass(qreal mass)=0;
    virtual void setFallInertia(QVector3D fallInertia)=0;


signals:
    void maskChanged(int mask);
    void groupChanged(int group);
    void kinematicChanged(bool kinematic);

    void worldTransformationChanged(QMatrix4x4 m);

    void fallInertiaChanged(QVector3D fallInertia);
    void massChanged(qreal mass);

    void rollingFrictionChanged(qreal rollingFriction);
    void frictionChanged(qreal friction);
    void restitutionChanged(qreal restitution);

public slots:

    virtual void applyForce(QVector3D force,QVector3D relationPosition=QVector3D());
    virtual void applyImpulse(QVector3D force,QVector3D relationPosition=QVector3D());
    virtual void clearForces();
    void onParentChanged(QQuickItem* parent);

protected:
    virtual void clear()=0;

    int m_mask;
    int m_group;
    bool m_kinematic;

    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;

    btCollisionShape* m_shape ;
    MotionState* m_motionState;
    btRigidBody::btRigidBodyConstructionInfo* m_rigidBodyCI;
    btRigidBody* m_rigidBody;

    Bullet::World* m_world;

    QMatrix4x4 m_worldTransformation;

};

}
#endif // ABSTRACTBODY_H
