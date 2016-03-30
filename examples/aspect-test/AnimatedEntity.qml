import Qt3D.Core 2.0
import Qt3D.Render 2.0
import QtPhysics.unofficial 1.0
import QtQuick 2.0 as QQ2
import Qt3D.Input 2.0



Entity {
    id: sceneRoot
    objectName: "Root"
    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, -10.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    Configuration  {
        controlledCamera: camera
    }

    MouseController {
        id: mouseController
    }
    components: [
        FrameGraph {
            activeFrameGraph: Viewport {
                id: viewport
                rect: Qt.rect(0, 0.0, 1.0, 1.0) // From Top Left
                clearColor: Qt.rgba(0, 0.5, 1, 1)

                CameraSelector {
                    id : cameraSelector
                    camera: camera

                    ClearBuffer {
                        buffers : ClearBuffer.ColorDepthBuffer
                    }
                }
            }
        },
        PhysicsWorldInfo{
          gravity: Qt.vector3d(0,-10,0)
          debug:true
        }
    ]

    SphereMesh {
        id: torusMesh
        radius: 2
        //minorRadius: 1
        //rings: 50
        //slices: 50
        //radius:4
        //length: 10
    }

    Transform {
        id: torusTransform
        /*Rotate{
            axis: Qt.vector3d(1,0,0)
            angle: 2
        }*/
//        Translate{
//            id:torusTranslate
//        }
    }

    PhysicsBodyInfo{
        id:torusBodyinfo
        mass:1
        restitution: 1
        inputTransform: torusTransform

    }

        Entity {
            id: torusEntity
            objectName: "torus"


//            property MouseInput mouseInput : MouseInput {
//                        controller: mouseController

//                        onReleased: {
//                            switch (mouse.button) {
//                            case Qt.LeftButton:
//                                torusTranslate.setDy(10+Math.random());
//                                break;
//                            }
//                        }
//                    }


            components: [ torusMesh, torusBodyinfo, torusBodyinfo.outputTransform ]
        }

//    Transform {
//        id: torusTransform2
////       Translate{
////           id:translation
////           //dx:20
////           dy:80
////           dz:-1
////       }
//    }
//    QQ2.NumberAnimation {
//            target: translation
//            property: "dy"
//            duration: 10000
//            from: 80
//            to: -60
//            loops: QQ2.Animation.Infinite
//            running: true
//        }
//    TorusMesh {
//        id: torusMesh2
//        radius: 15
//        minorRadius: 10
//        rings: 100
//        slices: 25
//    }

//    PhysicsBodyInfo{
//        id:torusBodyinfo2
//        mass:1
//        restitution: 1
//        kinematic: true
//        inputTransform: torusTransform2
//        onCollided: {console.log(event.target)}
//        onCollisionsListChanged:console.log(collisionsList.length)
//        onHasCollidedChanged: console.log(hasCollided);
//    }

//    SphereMesh {
//        id: sphereMesh
//        radius: 30
//    }

//    Transform {
//        id: sphereTransform
//    }
//    PhysicsBodyInfo{
//        id:sphereBody
//        restitution: 1
//        kinematic:true
//        mass:1
//        onCollided: console.log(parent.objectName)
//    }
////    SceneLoader{
////        id:sceneloader
////        source: "qrc:/Model1.dae"
////        onStatusChanged: {if(status==SceneLoader.Loaded) physicssetter.onAnyChange();}
////    }

////    PhysicsSetter{
////        id:physicssetter
////        bodyInfo: sphereBody
////        entityName: "Sphere"
////        sceneroot: sphereEntity
////    }

////    Entity {
////        objectName: "Sphere"
////        id: sphereEntity
////        components: [ sceneloader, sphereTransform ]
////    }
//    Entity{
//        id: torusEntity2
//        objectName: "torus2"
//        components: [ torusMesh2, torusBodyinfo2, torusBodyinfo2.outputTransform ]
//    }

    /*Floor is an entity non renderable
    but defined by the shape details*/
    Entity{
        objectName: "Floor"
        PlaneMesh{
            id: planeMesh
            height: 10
            width: 10
        }
        Transform{
            id:transformFloor
            matrix: {
                        var m = Qt.matrix4x4();
                        //m.rotate(25, Qt.vector3d(0, 0, 1))
                        m.translate(Qt.vector3d(0, -10, 0));
                        return m;
                    }
            onMatrixChanged:console.log(matrix)
        }
        PhysicsBodyInfo{
            id:floorBodyInfo
            restitution: 1
            inputTransform: transformFloor
            //shapeDetails:{"Type":"StaticPlane","PlaneConstant":0,"PlaneNormal": Qt.vector3d(0, 1, 0) }
        }
        components: [planeMesh,transformFloor,floorBodyInfo]
    }



}
