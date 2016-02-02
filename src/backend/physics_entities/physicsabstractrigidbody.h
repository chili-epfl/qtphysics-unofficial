#ifndef PHYSICSABSTRACTRIGIDBODY_H
#define PHYSICSABSTRACTRIGIDBODY_H
#include <qtphysicsunofficial_global.h>

#include <QObject>

namespace Physics {

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsAbstractRigidBody : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsAbstractRigidBody(QObject *parent = 0);

    virtual int mask()=0;
    virtual int group()=0;
    virtual void setMask(int mask)=0;
    virtual void setGroup(int group)=0;
    virtual bool kinematic()=0;
    virtual void setKinematic(bool kinematic)=0;


    virtual qreal mass()=0;
    virtual QVector3D fallInertia()=0;
    virtual qreal restitution()=0;
    virtual qreal rollingFriction()=0;
    virtual qreal friction()=0;
    virtual QMatrix4x4 worldTransformation()=0;

    virtual void setMass(qreal mass)=0;
    virtual void setFallInertia(QVector3D fallInertia)=0;
    virtual void setRestitution(qreal restitution)=0;
    virtual void setRollingFriction(qreal rollingFriction)=0;
    virtual void setFriction(qreal friction)=0;
    virtual void setWorldTransformation(QMatrix4x4 m)=0;


protected:

signals:

public slots:
};

}
#endif // PHYSICSABSTRACTRIGIDBODY_H
