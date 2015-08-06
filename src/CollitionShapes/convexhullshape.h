#ifndef CONVEXHULLSHAPE_H
#define CONVEXHULLSHAPE_H
#include "abstractcollitionshape.h"

namespace Bullet {

class ConvexHullShape : public AbstractCollitionShape
{
    Q_OBJECT
public:
    ConvexHullShape(QQuickItem* parent=0);
    ~ConvexHullShape();
    void setFallInertia(QVector3D fallInertia){};
    void setMass(qreal mass){};
private:
    void init();
    void clear();
};

}
#endif // CONVEXHULLSHAPE_H
