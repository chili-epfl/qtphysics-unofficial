#ifndef PHYSICSBODYINFO_H
#define PHYSICSBODYINFO_H
#include "frontend_global.h"

#include <Qt3DCore>
#include <QVector3D>

namespace Physics {

class FRONTENDSHARED_EXPORT PhysicsBodyInfo: public Qt3D::QComponent
{
    Q_OBJECT
    Q_PROPERTY(bool shareable READ shareable)
    Q_PROPERTY(int mask READ mask WRITE setMask NOTIFY maskChanged)
    Q_PROPERTY(int group READ group WRITE setGroup NOTIFY groupChanged)

    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(qreal rollingFriction READ rollingFriction WRITE setRollingFriction NOTIFY rollingFrictionChanged)
    Q_PROPERTY(qreal mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(QVector3D fallInertia READ fallInertia WRITE setFallInertia NOTIFY fallInertiaChanged)
    /*Shape details allows to override the details of the collition shape that otherwise would be
    * derived by the mesh. It's also useful to create object with a specific collition shape but with an empty mesh*/
    Q_PROPERTY(QVariantMap shapeDetails READ shapeDetails WRITE setShapeDetails NOTIFY shapeDetailsChanged)
public:
    explicit PhysicsBodyInfo(Qt3D::QNode* parent=0);
    ~PhysicsBodyInfo();
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &change) Q_DECL_OVERRIDE;

    virtual int mask(){return m_mask;}
    virtual int group(){return m_group;}

    virtual void setMask(int mask);
    virtual void setGroup(int group);

    virtual qreal restitution(){return m_restitution;}
    virtual qreal rollingFriction(){return m_rollingFriction;}
    virtual qreal friction(){return m_friction;}
    virtual qreal mass(){return m_mass;}
    virtual QVector3D fallInertia(){return m_fallInertia;}
    virtual const QVariantMap& shapeDetails(){return m_shapeDetails;}

    virtual void setRestitution(qreal restitution);
    virtual void setRollingFriction(qreal rollingFriction);
    virtual void setFriction(qreal friction);
    virtual void setMass(qreal mass);
    virtual void setFallInertia(QVector3D fallInertia);
    virtual void setShapeDetails(QVariantMap shapeDetails);

signals:
    void maskChanged(int mask);
    void groupChanged(int group);

    void fallInertiaChanged(QVector3D fallInertia);
    void massChanged(qreal mass);
    void rollingFrictionChanged(qreal rollingFriction);
    void frictionChanged(qreal friction);
    void restitutionChanged(qreal restitution);
    void shapeDetailsChanged();

protected:
    void copy(const Qt3D::QNode *ref) Q_DECL_OVERRIDE;
private:
    QT3D_CLONEABLE(PhysicsBodyInfo)

    int m_mask;
    int m_group;

    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;
    QVariantMap m_shapeDetails;

    Qt3D::QMatrixTransform* m_attached_matrix;

};

}
#endif // PHYSICSBODYINFO_H
