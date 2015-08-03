#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QQuickItem>
#include <QVector3D>
#include <QMatrix4x4>

namespace Bullet{

class RigidBody : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(RigidBody)
public:
    RigidBody(QQuickItem *parent = 0);
signals:

public slots:

private:
    qreal m_mass;
    QVector3D m_fallInertia;
    QMatrix4x4 transformation;

};

}

#endif // RIGIDBODY_H
