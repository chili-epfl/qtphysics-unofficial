#include "convexhullshape.h"
namespace Physics {

namespace Bullet {


ConvexHullShape::ConvexHullShape(QObject* parent):
    AbstractBody(parent)
{
    setMass(1.0f);
    initShape();
    initBody();
}
ConvexHullShape::ConvexHullShape(qreal* points,int n_points,QObject* parent):
    AbstractBody(parent)
{
    setMass(1.0f);
    initShape(points,n_points);
    initBody();
}

ConvexHullShape::~ConvexHullShape(){

}

void ConvexHullShape::initShape(qreal* points,int n_points){

    btScalar* bt_points=new btScalar[3*n_points];

    for(int i=0;i<3*n_points;i++)
        bt_points[i]=points[i];

    m_shape = new btConvexHullShape(bt_points,n_points);

    delete bt_points;
}

void ConvexHullShape::addPoint(QVector3D p){
    ((btConvexHullShape*)m_shape)->addPoint(btVector3(p.x(),p.y(),p.z()));
}

}}
