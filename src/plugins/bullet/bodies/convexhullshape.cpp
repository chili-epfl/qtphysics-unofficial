#include "convexhullshape.h"
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
namespace Physics {

namespace Bullet {


ConvexHullShape::ConvexHullShape(QObject* parent):
    AbstractBody(parent)
{
    initShape();
    initBody();
}
ConvexHullShape::ConvexHullShape(qreal* points,int n_points,QObject* parent):
    AbstractBody(parent)
{
    initShape(points,n_points);
    initBody();

}

ConvexHullShape::~ConvexHullShape(){

}
void ConvexHullShape::initShape(){
    initShape(Q_NULLPTR,0);
}

void ConvexHullShape::initShape(qreal* points,int n_points){
    m_shape = new btConvexHullShape();
    for(int i=0;i<3*n_points;i=i+3){
        btVector3 point(points[i],points[i+1],points[i+2]);
        ((btConvexHullShape*)m_shape)->addPoint(point);
    }
    btShapeHull* hull = new btShapeHull((btConvexHullShape*)m_shape);
    btScalar margin = m_shape->getMargin();
    hull->buildHull(margin);
    btConvexHullShape* old_shape=(btConvexHullShape*)m_shape;
    m_shape = new btConvexHullShape();
    for(int i=0;i<hull->numVertices();i++){
        ((btConvexHullShape*)m_shape)->addPoint(hull->getVertexPointer()[i]);
    }
    delete old_shape;

}

void ConvexHullShape::addPoint(QVector3D p){
    ((btConvexHullShape*)m_shape)->addPoint(btVector3(p.x(),p.y(),p.z()));
}

void ConvexHullShape::updatePoints(qreal* points,int n_points){
    delete m_shape;
    btScalar* bt_points=new btScalar[3*n_points];
    for(int i=0;i<3*n_points;i++)
        bt_points[i]=points[i];
    m_shape = new btConvexHullShape(bt_points,n_points);
    m_rigidBody->setCollisionShape(m_shape);
    delete bt_points;
    setMassProps();
}



}}
