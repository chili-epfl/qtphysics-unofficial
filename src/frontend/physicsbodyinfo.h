#ifndef PHYSICSBODYINFO_H
#define PHYSICSBODYINFO_H
#include "frontend_global.h"

#include <QVector3D>
#include "physicscollisionevent.h"
#include <QQmlListProperty>
namespace Physics {

class FRONTENDSHARED_EXPORT PhysicsBodyInfo:
        #if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
        public Qt3DCore::QComponent
        #else
        public Qt3D::QComponent
        #endif

{
    Q_OBJECT
    Q_PROPERTY(bool shareable READ shareable)
    Q_PROPERTY(int mask READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(int group READ group WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(bool kinematic READ kinematic WRITE setKinematic NOTIFY kinematicChanged)

    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal rollingFriction READ rollingFriction WRITE setRollingFriction NOTIFY rollingFrictionChanged)
    Q_PROPERTY(qreal mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(QVector3D fallInertia READ fallInertia WRITE setFallInertia NOTIFY fallInertiaChanged)

    Q_PROPERTY(bool hasCollided READ hasCollided NOTIFY hasCollidedChanged)
    Q_PROPERTY(QQmlListProperty<Physics::PhysicsCollisionEvent> collisionsList READ collisionsList NOTIFY collisionsListChanged)

    /*Shape details allows to override the details of the collision shape that otherwise would be
    * derived by the mesh. It's also useful to create object with a specific collision shape but with an empty mesh*/
    Q_PROPERTY(QVariantMap shapeDetails READ shapeDetails WRITE setShapeDetails NOTIFY shapeDetailsChanged)
    Q_PROPERTY(Qt3DCore::QTransform* inputTransform READ inputTransform WRITE setInputTransform NOTIFY inputTransformChanged)
    Q_PROPERTY(Qt3DCore::QTransform* outputTransform READ outputTransform NOTIFY outputTransformChanged)

public:
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    explicit PhysicsBodyInfo(Qt3DCore::QNode* parent=0);
#else
    explicit PhysicsBodyInfo(Qt3D::QNode* parent=0);
#endif
    ~PhysicsBodyInfo();
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change) Q_DECL_OVERRIDE;
#else
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &change) Q_DECL_OVERRIDE;
#endif

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
    virtual const QVariantMap& shapeDetails(){return m_shapeDetails;}
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    virtual Qt3DCore::QTransform* inputTransform(){return m_inputTransform;}
    virtual Qt3DCore::QTransform* outputTransform(){return m_outputTransform;}
#else
    virtual Qt3D::QTransform* inputTransform(){return m_inputTransform;}
    virtual Qt3D::QTransform* outputTransform(){return m_outputTransform;}
#endif


    virtual void setRestitution(qreal restitution);
    virtual void setRollingFriction(qreal rollingFriction);
    virtual void setFriction(qreal friction);
    virtual void setMass(qreal mass);
    virtual void setFallInertia(QVector3D fallInertia);
    virtual void setShapeDetails(QVariantMap shapeDetails);
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    virtual void setInputTransform(Qt3DCore::QTransform* inputTransform);
#else
    virtual void setInputTransform(Qt3D::QTransform* inputTransform);
#endif

    QQmlListProperty<PhysicsCollisionEvent> collisionsList();
    bool hasCollided(){return m_hasCollided;}

#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    bool collisionTest(Qt3DCore::QNodeId);
#else
    bool collisionTest(Qt3D::QNodeId);
#endif

signals:
    void maskChanged(int mask);
    void groupChanged(int group);
    void kinematicChanged(bool kinematic);

    void fallInertiaChanged(QVector3D fallInertia);
    void massChanged(qreal mass);
    void rollingFrictionChanged(qreal rollingFriction);
    void frictionChanged(qreal friction);
    void restitutionChanged(qreal restitution);
    void shapeDetailsChanged();
    void inputTransformChanged();
    void outputTransformChanged();

    void collided(Physics::PhysicsCollisionEvent* event);
    void hasCollidedChanged(bool val);
    void collisionsListChanged();
protected:
    void copy(const Qt3DCore::QNode *ref) Q_DECL_OVERRIDE;

    QT3D_CLONEABLE(PhysicsBodyInfo)

    int m_mask;
    int m_group;
    bool m_kinematic;

    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;
    QVariantMap m_shapeDetails;

#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    Qt3DCore::QTransform* m_inputTransform;
    Qt3DCore::QTransform* m_outputTransform;
    Qt3DRender::QMatrixTransform* m_outputTransform_matrix;
#else
    Qt3D::QTransform* m_inputTransform;
    Qt3D::QTransform* m_outputTransform;
    Qt3D::QMatrixTransform* m_outputTransform_matrix;
#endif


    PhysicsCollisionEventPtrList m_collisionsList;
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
    QSet<Qt3DCore::QNodeId> m_collisionsCache;
#else
    QSet<Qt3D::QNodeId> m_collisionsCache;
#endif
    bool m_hasCollided;

    static PhysicsCollisionEvent *qmlComponentAt(QQmlListProperty<PhysicsCollisionEvent> *list, int index);
    static int qmlComponentsCount(QQmlListProperty<PhysicsCollisionEvent> *list);

};

}
#endif // PHYSICSBODYINFO_H
