#ifndef CONVEXHULLSHAPE_H
#define CONVEXHULLSHAPE_H
#include "abstractbody.h"

namespace Bullet {

class ConvexHullShape : public AbstractCollitionShape
{
    Q_OBJECT
public:
    ConvexHullShape(QQuickItem* parent=0);
    ConvexHullShape(qreal* points,int n_points,QQuickItem* parent=0);
    ~ConvexHullShape();

    void setFallInertia(QVector3D fallInertia);
    void setMass(qreal mass);
    void addPoint(QVector3D p);
private:
    void init(qreal* points=NULL,int n_points=0);
    void clear();
};

}
#endif // CONVEXHULLSHAPE_H
