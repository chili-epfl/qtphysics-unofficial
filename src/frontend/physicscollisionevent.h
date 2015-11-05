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
    Q_PROPERTY(QVector3D contactPointOnBodyLocal READ contactPointOnBodyLocal)
    Q_PROPERTY(QVector3D contactPointOnTargetLocal READ contactPointOnTargetLocal)

public:
    explicit PhysicsCollisionEvent(QObject* parent=0);
    Qt3D::QNodeId target(){ return m_target;}
    QVector3D contactPointOnBody(){return m_contactPointOnBody;}
    QVector3D contactPointOnTarget(){return m_contactPointOnTarget;}
    QVector3D contactPointOnBodyLocal(){return m_contactPointOnBodyLocal;}
    QVector3D contactPointOnTargetLocal(){return m_contactPointOnTargetLocal;}
    QVector3D normalOnTarget(){return m_normalOnTarget;}

    bool isNew(){return m_isNew;}

    void setTarget(Qt3D::QNodeId target);
    void setContactPointOnBody(QVector3D point);
    void setContactPointOnTarget(QVector3D point);
    void setContactPointOnBodyLocal(QVector3D point);
    void setContactPointOnTargetLocal(QVector3D point);
    void setNormalOnTarget(QVector3D normal);
    void setIsNew(bool val);
private:
    Qt3D::QNodeId m_target;
    QVector3D m_contactPointOnBody;
    QVector3D m_contactPointOnTarget;
    QVector3D m_contactPointOnBodyLocal;
    QVector3D m_contactPointOnTargetLocal;
    QVector3D m_normalOnTarget;
    bool m_isNew;
};

typedef QSharedPointer<PhysicsCollisionEvent> PhysicsCollisionEventPtr;
typedef QList<PhysicsCollisionEventPtr> PhysicsCollisionEventPtrList;
typedef QList<PhysicsCollisionEvent> PhysicsCollisionEventList;

}


#endif // PHYSICSCOLLISIONEVENT_H
