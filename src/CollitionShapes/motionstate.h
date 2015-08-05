#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include <QObject>
#include <bullet/LinearMath/btDefaultMotionState.h>
#include <QMatrix4x4>
namespace Bullet{

class MotionState : public QObject, public btDefaultMotionState
{
    Q_OBJECT
public:
    MotionState(QObject *parent = 0);
    MotionState(const btTransform &startTrans=btTransform::getIdentity(), const btTransform &centerOfMassOffset=btTransform::getIdentity(),QObject* parent=0);
    MotionState(const QMatrix4x4 startTrans, const QMatrix4x4 centerOfMassOffset,QObject* parent=0);
    virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const;
    virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);
    void setWorldTransform(QMatrix4x4 mat);

    QMatrix4x4 getWorldTransformAsQMatrix4x4();
signals:
    void motionStateChanged(QMatrix4x4 mat);

public slots:
};
}
#endif // MOTIONSTATE_H
