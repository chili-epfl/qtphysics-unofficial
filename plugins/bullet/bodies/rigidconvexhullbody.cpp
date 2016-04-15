#include <bodies/rigidconvexhullbody.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
#include <LinearMath/btGeometryUtil.h>

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

    btAlignedObjectArray<btVector3> planes,vertices;
    for(int i=0;i<hull->numVertices();i++){
        vertices.push_back(hull->getVertexPointer()[i]);
    }
    btGeometryUtil::getPlaneEquationsFromVertices(vertices, planes);

    int sz = planes.size();
    bool tooSmall = false;
    for (int i=0 ; i<sz ; ++i) {
       if ((planes[i][3] += m_shape->getMargin()) >= 0) {
          tooSmall = true;
          break;
       }
    }

    if (!tooSmall) {
       qWarning("Convex hull too small to apply margin");
       vertices.clear();
       btGeometryUtil::getVerticesFromPlaneEquations(planes, vertices);
    }

    sz = vertices.size();
    for (int i=0 ; i<sz ; ++i) {
       ((btConvexHullShape*)m_shape)->addPoint(vertices[i]);
    }
    delete hull;
}
void RigidConvexHullBody::setCollisionMargin(qreal margin){

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
