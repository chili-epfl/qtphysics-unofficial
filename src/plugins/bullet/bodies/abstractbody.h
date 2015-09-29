#ifndef ABSTRACTBODY_H
#define ABSTRACTBODY_H
#include <physics_entities/physicsabstractrigidbody.h>

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include <QVector3D>
#include <QMatrix4x4>

namespace Physics {

namespace Bullet {


class AbstractBody : public PhysicsAbstractRigidBody {
    Q_OBJECT

public:
    enum ChangeFlag{
        NoChange =0,
        MaskChanged=1,
        GroupChanged=2
    };
    Q_DECLARE_FLAGS(ChangeFlags, ChangeFlag)
    explicit AbstractBody(QObject* parent=0);

    virtual int mask(){return m_mask;}
    virtual int group(){return m_group;}
    virtual bool kinematic(){return m_kinematic;}

    virtual void setMask(int mask);
    virtual void setGroup(int group);
    virtual void setKinematic(bool kinematic);

    virtual QMatrix4x4 worldTransformation();
    virtual void setWorldTransformation(QMatrix4x4 m);

    virtual qreal restitution(){return m_restitution;}
    virtual qreal rollingFriction(){return m_rollingFriction;}
    virtual qreal friction(){return m_friction;}
    virtual qreal mass(){return m_mass;}
    virtual QVector3D fallInertia(){return m_fallInertia;}

    virtual void setRestitution(qreal restitution);
    virtual void setRollingFriction(qreal rollingFriction);
    virtual void setFriction(qreal friction);
    virtual void setMass(qreal mass);
    virtual void setFallInertia(QVector3D fallInertia);

    btRigidBody* bulletBody(){return m_rigidBody;}
public slots:

    virtual void applyForce(QVector3D force,QVector3D relationPosition=QVector3D());
    virtual void applyImpulse(QVector3D force,QVector3D relationPosition=QVector3D());
    virtual void clearForces();
signals:
    void worldUpdateRequired();
protected:
    virtual void initBody();
    virtual void initShape()=0;
    virtual void setMassProps();

    int m_mask;
    int m_group;
    bool m_kinematic;
    ChangeFlags m_changeFlags;
    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;

    btCollisionShape* m_shape ;
    btMotionState* m_motionState;

    btRigidBody* m_rigidBody;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(AbstractBody::ChangeFlags)
}}
#endif // ABSTRACTBODY_H
