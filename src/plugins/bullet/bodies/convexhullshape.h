#ifndef CONVEXHULLSHAPE_H
#define CONVEXHULLSHAPE_H
#include "abstractbody.h"
namespace Physics {

namespace Bullet {

class ConvexHullShape : public AbstractBody
{
    Q_OBJECT
public:
    explicit ConvexHullShape(QObject* parent=0);
    explicit ConvexHullShape(qreal* points,int n_points,QObject* parent=0);
    ~ConvexHullShape();
    void addPoint(QVector3D p);
protected:
    void initShape(qreal* points,int n_points);
    void initShape()Q_DECL_OVERRIDE;
private:
};

}}
#endif // CONVEXHULLSHAPE_H
