#ifndef PHYSICSCOLLISIONEVENT_H
#define PHYSICSCOLLISIONEVENT_H
#include "frontend_global.h"

#include <Qt3DCore>
#include <QVector3D>

namespace Physics {


class FRONTENDSHARED_EXPORT PhysicsCollisionEvent: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QEntity* target READ target)
    Q_PROPERTY(QVector3D contactPointOnBody READ contactPointOnBody)
    Q_PROPERTY(QVector3D contactPointOnTarget READ contactPointOnTarget)
    Q_PROPERTY(QVector3D normalOnTarget READ normalOnTarget)

    explicit PhysicsCollisionEvent(QObject* parent=0);

    Qt3D::QEntity* target(){ return m_target;}
    QVector3D contactPointOnBody(){return m_contactPointOnBody;}
    QVector3D contactPointOnTarget(){return m_contactPointOnTarget;}
    QVector3D normalOnTarget(){return m_normalOnTarget;}

    void setTarget(Qt3D::QEntity* target);
    void setContactPointOnBody(QVector3D point);
    void setContactPointOnTarget(QVector3D point);
    void setNormalOnTarget(QVector3D normal);

private:

    Qt3D::QEntity* m_target;
    QVector3D m_contactPointOnBody;
    QVector3D m_contactPointOnTarget;
    QVector3D m_normalOnTarget;
};
typedef QSharedPointer<PhysicsCollisionEvent> PhysicsCollisionEventPtr;
}


#endif // PHYSICSCOLLISIONEVENT_H
