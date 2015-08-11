#ifndef CONVEXHULLSHAPE_H
#define CONVEXHULLSHAPE_H
#include "abstractbody.h"
namespace Physics {

namespace Bullet {

class ConvexHullShape : public AbstractBody
{
    Q_OBJECT
public:
    ConvexHullShape(QObject* parent=0);
    ConvexHullShape(qreal* points,int n_points,QObject* parent=0);
    ~ConvexHullShape();
    void addPoint(QVector3D p);
protected:
    void initShape(qreal* points=NULL,int n_points=0) Q_DECL_OVERRIDE;

private:
};

}}
#endif // CONVEXHULLSHAPE_H
