#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include "abstractcollitionshape.h"
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <QVector3D>


namespace Bullet {

class BoxShape: public AbstractCollitionShape
{
    Q_OBJECT
    Q_PROPERTY(QVector3D dimenion READ dimension WRITE setDimension NOTIFY dimensionChanged)
public:
    BoxShape(QQuickItem* parent=0);
    ~BoxShape();
    QVector3D dimension(){return m_dimension;}
    void setDimension(QVector3D dimention);
    void setFallInertia(QVector3D fallInertia);
    void setMass(qreal mass);
signals:
    void dimensionChanged(QVector3D val);
private:
    void init();
    void clean();
    QVector3D m_dimension;
};
}
#endif // BOXSHAPE_H
