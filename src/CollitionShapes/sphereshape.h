#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include "abstractcollitionshape.h"
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>

namespace Bullet {

class SphereShape: public AbstractCollitionShape
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    SphereShape(QQuickItem* parent=0);
    ~SphereShape();
    qreal radius(){return m_radius;}
    void setRadius(qreal radius);
    void setFallInertia(QVector3D fallInertia);
    void setMass(qreal mass);
signals:
    void radiusChanged(qreal radius);

private:
    void init();
    void clear();

    qreal m_radius;
};

}
#endif // SPHERESHAPE_H
