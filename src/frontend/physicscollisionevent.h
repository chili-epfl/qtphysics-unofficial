#ifndef PHYSICSCOLLISIONEVENT_H
#define PHYSICSCOLLISIONEVENT_H
#include "frontend_global.h"

#include <Qt3DCore>
#include <QVector3D>
#include <QDebug>
namespace Physics {


class FRONTENDSHARED_EXPORT PhysicsCollisionEvent: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QNodeId target READ target)
    Q_PROPERTY(QVector3D contactPointOnBody READ contactPointOnBody)
    Q_PROPERTY(QVector3D contactPointOnTarget READ contactPointOnTarget)
    Q_PROPERTY(QVector3D normalOnTarget READ normalOnTarget)
public:
    explicit PhysicsCollisionEvent(QObject* parent=0);
    Qt3D::QNodeId target(){ return m_target;}
    QVector3D contactPointOnBody(){return m_contactPointOnBody;}
    QVector3D contactPointOnTarget(){return m_contactPointOnTarget;}
    QVector3D normalOnTarget(){return m_normalOnTarget;}

    void setTarget(Qt3D::QNodeId target);
    void setContactPointOnBody(QVector3D point);
    void setContactPointOnTarget(QVector3D point);
    void setNormalOnTarget(QVector3D normal);

private:

    Qt3D::QNodeId m_target;
    QVector3D m_contactPointOnBody;
    QVector3D m_contactPointOnTarget;
    QVector3D m_normalOnTarget;
};
typedef QSharedPointer<PhysicsCollisionEvent> PhysicsCollisionEventPtr;
}


#endif // PHYSICSCOLLISIONEVENT_H
