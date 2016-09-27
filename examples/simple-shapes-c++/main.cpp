#include <QGuiApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QCuboidMesh>

#include <QPropertyAnimation>

#include "qt3dwindow.h"
#include <QtPhysicsUnofficial/frontend/physicsbodyinfo.h>
#include <QtPhysicsUnofficial/frontend/physicsworldinfo.h>

#include <QtPhysicsUnofficial/frontend/physicsaspect.h>

Qt3DCore::QEntity *createScene()
{
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    Physics::PhysicsWorldInfo* world=new Physics::PhysicsWorldInfo();
    world->setGravity(QVector3D(0,-10,0));

    rootEntity->addComponent(world);

    // Material
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);

    // Sphere
    Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(3);

    Physics::PhysicsBodyInfo* sphere_body=new Physics::PhysicsBodyInfo();
    sphere_body->setMass(10);
    sphere_body->setRestitution(1);

    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphere_body->outputTransform());
    sphereEntity->addComponent(material);
    sphereEntity->addComponent(sphere_body);

    //Floor

    Qt3DCore::QEntity* floor=new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCuboidMesh* plane_mesh=new Qt3DExtras::QCuboidMesh();
    plane_mesh->setXExtent(100);
    plane_mesh->setYExtent(1);
    plane_mesh->setZExtent(100);
    Qt3DCore::QTransform *floorTransform = new Qt3DCore::QTransform();
    floorTransform->setTranslation(QVector3D(0,-20,0));

    Physics::PhysicsBodyInfo* floor_body=new Physics::PhysicsBodyInfo();
    floor_body->setMass(0);
    floor_body->setRestitution(1);

    floor_body->setInputTransform(floorTransform);

    floor->addComponent(floor_body);
    floor->addComponent(floorTransform);
    floor->addComponent(plane_mesh);
    floor->addComponent(material);

    return rootEntity;
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;



    Qt3DCore::QEntity *scene = createScene();

    // Camera
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 40, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    view.registerAspect(new Physics::PhysicsAspect());
    view.setRootEntity(scene);
    view.show();

    return app.exec();
}
