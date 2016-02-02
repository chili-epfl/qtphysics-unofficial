#include <bulletfactory.h>

#include <worlds/dynamicsworld.h>
#include <bodies/rigidboxbody.h>
#include <bodies/rigidconvexhullbody.h>
#include <bodies/rigidstaticplanebody.h>
#include <bodies/rigidspherebody.h>

namespace Physics {

namespace Bullet {
BulletFactory::BulletFactory(QObject *parent) :
    QObject(parent)
{
}

PhysicsAbstractRigidBody* BulletFactory::create_rigid_body(QVariantMap geometric_info){
    if(geometric_info.contains("Type")){
        QString type=geometric_info["Type"].toString();
        if(type=="Cuboid"){
            RigidBoxBody* b=new RigidBoxBody();
            b->setDimension(QVector3D(geometric_info["X_Dim"].toFloat(),
                            geometric_info["Y_Dim"].toFloat(),
                            geometric_info["Z_Dim"].toFloat()));
            return b;
        }
        else if(type=="Sphere"){
            RigidSphereBody* b=new RigidSphereBody();
            b->setRadius(geometric_info["Radius"].toFloat());
            return b;
        }
        else if(type=="StaticPlane"){
            RigidStaticPlaneBody* b=new RigidStaticPlaneBody();
            b->setPlaneConstant(geometric_info["PlaneConstant"].toFloat());
            b->setNormal(geometric_info["PlaneNormal"].value<QVector3D>());
            return b;
        }
        else if(type=="Generic" ){
            QVector<QVector3D> points=geometric_info["Points"].value<QVector<QVector3D> >();
            qreal* _points=new qreal[points.size()*3];
            int i=0;
            Q_FOREACH(QVector3D p, points){
                //QVector3D _p=p.value<QVector3D>();
                _points[i]=p.x();
                _points[i+1]=p.y();
                _points[i+2]=p.z();
                i+=3;
            }
            RigidConvexHullBody* b=new RigidConvexHullBody(_points,points.size(),0);
            delete _points;
            return b;
        }
        else{
            qFatal("Invalid geometric info");
            return Q_NULLPTR;
        }
    }
    else{
        qFatal("Invalid geometric info");
        return Q_NULLPTR;
    }

}

PhysicsAbstractDynamicsWorld* BulletFactory::create_dynamics_world(){
    return new DynamicsWorld();
}




}

}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(bullet, BulletFactory)
#endif // QT_VERSION < 0x050000
