#ifndef PHYSICSBODYINFO_H
#define PHYSICSBODYINFO_H
#include <qtphysicsunofficial_global.h>

#include <QVector3D>
#include <frontend/physicscollisionevent.h>
#include <QQmlListProperty>
namespace Physics {

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBodyInfo:
        public Qt3DCore::QComponent
{
    Q_OBJECT
    Q_PROPERTY(bool isShareable READ isShareable NOTIFY shareableChanged)    Q_PROPERTY(int mask READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(int group READ group WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(bool kinematic READ kinematic WRITE setKinematic NOTIFY kinematicChanged)

    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal rollingFriction READ rollingFriction WRITE setRollingFriction NOTIFY rollingFrictionChanged)
    Q_PROPERTY(qreal mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(QVector3D fallInertia READ fallInertia WRITE setFallInertia NOTIFY fallInertiaChanged)

    Q_PROPERTY(bool hasCollided READ hasCollided NOTIFY hasCollidedChanged)
    Q_PROPERTY(QQmlListProperty<Physics::PhysicsCollisionEvent> collisionsList READ collisionsList NOTIFY collisionsListChanged)

    Q_PROPERTY(Qt3DCore::QTransform* inputTransform READ inputTransform WRITE setInputTransform NOTIFY inputTransformChanged)
    Q_PROPERTY(Qt3DCore::QTransform* outputTransform READ outputTransform NOTIFY outputTransformChanged)

public:
    explicit PhysicsBodyInfo(Qt3DCore::QNode* parent=0);
    //~PhysicsBodyInfo();
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change) Q_DECL_OVERRIDE;
    inline bool isShareable(){return true;}

    virtual int mask(){return m_mask;}
    virtual int group(){return m_group;}
    virtual bool kinematic(){return m_kinematic;}

    virtual void setMask(int mask);
    virtual void setGroup(int group);
    virtual void setKinematic(bool kinematic);

    virtual qreal restitution(){return m_restitution;}
    virtual qreal rollingFriction(){return m_rollingFriction;}
    virtual qreal friction(){return m_friction;}
    virtual qreal mass(){return m_mass;}
    virtual QVector3D fallInertia(){return m_fallInertia;}
    virtual Qt3DCore::QTransform* inputTransform(){return m_inputTransform;}
    virtual Qt3DCore::QTransform* outputTransform(){return m_outputTransform;}


    virtual void setRestitution(qreal restitution);
    virtual void setRollingFriction(qreal rollingFriction);
    virtual void setFriction(qreal friction);
    virtual void setMass(qreal mass);
    virtual void setFallInertia(QVector3D fallInertia);
    virtual void setInputTransform(Qt3DCore::QTransform* inputTransform);

    QQmlListProperty<PhysicsCollisionEvent> collisionsList();
    bool hasCollided(){return m_hasCollided;}

    bool collisionTest(Qt3DCore::QNodeId);

signals:
    void maskChanged(int mask);
    void groupChanged(int group);
    void kinematicChanged(bool kinematic);
    void shareableChanged();
    void fallInertiaChanged(QVector3D fallInertia);
    void massChanged(qreal mass);
    void rollingFrictionChanged(qreal rollingFriction);
    void frictionChanged(qreal friction);
    void restitutionChanged(qreal restitution);
    void inputTransformChanged();
    void outputTransformChanged();

    void collided(Physics::PhysicsCollisionEventPtr event);
    void hasCollidedChanged(bool val);
    void collisionsListChanged();
protected:
    //void copy(const Qt3DCore::QNode *ref) Q_DECL_OVERRIDE;

    //QT3D_CLONEABLE(PhysicsBodyInfo)

    int m_mask;
    int m_group;
    bool m_kinematic;

    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;

    Qt3DCore::QTransform* m_inputTransform;
    Qt3DCore::QTransform* m_outputTransform;



    PhysicsCollisionEventPtrList m_collisionsList;
    QSet<Qt3DCore::QNodeId> m_collisionsCache;
    bool m_hasCollided;

    static PhysicsCollisionEvent *qmlComponentAt(QQmlListProperty<PhysicsCollisionEvent> *list, int index);
    static int qmlComponentsCount(QQmlListProperty<PhysicsCollisionEvent> *list);
private:
    Qt3DCore::QNodeCreatedChangeBasePtr createNodeCreationChange() const Q_DECL_OVERRIDE;
};

struct PhysicsBodyInfoData{
    int mask;
    int group;
    bool kinematic;
    qreal mass;
    QVector3D fallInertia;
    qreal restitution;
    qreal friction;
    qreal rollingFriction;
    Qt3DCore::QNodeId inputTransformID;
};

}
#endif // PHYSICSBODYINFO_H
