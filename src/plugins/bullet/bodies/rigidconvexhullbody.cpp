#include "rigidconvexhullbody.h"
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
namespace Physics {

namespace Bullet {


RigidConvexHullBody::RigidConvexHullBody(QObject* parent):
    AbstractRigidBody(parent)
{
    initShape();
    initBody();
}
RigidConvexHullBody::RigidConvexHullBody(qreal* points,int n_points,QObject* parent):
    AbstractRigidBody(parent)
{
    initShape(points,n_points);
    initBody();

}

RigidConvexHullBody::~RigidConvexHullBody(){

}
void RigidConvexHullBody::initShape(){
    initShape(Q_NULLPTR,0);
}

void RigidConvexHullBody::initShape(qreal* points,int n_points){
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
        qDebug()<<hull->getVertexPointer()[i].x()<<" "<<hull->getVertexPointer()[i].y()<<" "<<hull->getVertexPointer()[i].z();
        ((btConvexHullShape*)m_shape)->addPoint(hull->getVertexPointer()[i]);
    }
    delete old_shape;
    qDebug()<<"end";

}

void RigidConvexHullBody::addPoint(QVector3D p){
    ((btConvexHullShape*)m_shape)->addPoint(btVector3(p.x(),p.y(),p.z()));
}

void RigidConvexHullBody::updatePoints(qreal* points,int n_points){
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
