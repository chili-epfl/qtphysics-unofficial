#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include <QObject>
#include <QMatrix4x4>
#include <bullet/LinearMath/btDefaultMotionState.h>

namespace Physics {


namespace Bullet{

class MotionState : public QObject, public btDefaultMotionState
{
    Q_OBJECT
public:
    explicit MotionState(QObject *parent = 0);
    explicit MotionState(const btTransform &startTrans=btTransform::getIdentity(), const btTransform &centerOfMassOffset=btTransform::getIdentity(),QObject* parent=0);
    explicit MotionState(const QMatrix4x4 startTrans, const QMatrix4x4 centerOfMassOffset,QObject* parent=0);
    virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const;
    virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);
    void setWorldTransform(QMatrix4x4 mat);
    QMatrix4x4 getWorldTransformAsQMatrix4x4();
public slots:
};
}
}
#endif // MOTIONSTATE_H
