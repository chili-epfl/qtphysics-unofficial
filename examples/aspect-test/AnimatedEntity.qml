import Qt3D.Core 2.0
import Qt3D.Render 2.0
import QtPhysics.unofficial 1.0
import QtQuick 2.0 as QQ2
import Qt3D.Input 2.0
import Qt3D.Extras 2.0


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
        position: Qt.vector3d( 0.0, 0.0, -20.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }
    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }
        },PhysicsWorldInfo{
            gravity: Qt.vector3d(0,-10,0)
            scaleFactor: 1
        }
    ]
    PhongMaterial{
        id:material
    }
    SphereMesh {
        id: torusMesh
        radius: 2
    }

    Transform {
        id: torusTransform
        translation:Qt.vector3d(0,-5,0)
    }

    PhysicsBodyInfo{
        id:torusBodyinfo
        mass:3
        kinematic: true
        restitution: 1
        inputTransform: torusTransform
    }

    Entity {
        id: torusEntity
        objectName: "torus"
        components: [ torusMesh, torusBodyinfo, material, torusBodyinfo.outputTransform ]
    }

    Transform {
        id: torusTransform2
        translation:Qt.vector3d(0,10,0)
    }

    TorusMesh {
        id: torusMesh2
        radius: 1
        minorRadius: 1
        rings: 100
        slices: 25
    }

    PhysicsBodyInfo{
        id:torusBodyinfo2
        mass:1
        restitution: 1
        inputTransform: torusTransform2

    }


    Entity{
        id: torusEntity2
        objectName: "torus2"
        components: [ torusMesh2, material,torusBodyinfo2, torusBodyinfo2.outputTransform ]
    }

    Entity{
        objectName: "Floor"
        CuboidMesh{
            id: planeMesh
            xExtent: 100
            yExtent: 5
            zExtent: 100
        }
        Transform{
            id:transformFloor
            matrix: {
                var m = Qt.matrix4x4();
                m.translate(Qt.vector3d(0, -10, 0));
                return m;
            }
        }
        PhysicsBodyInfo{
            id:floorBodyInfo
            restitution: 1
            inputTransform: transformFloor
        }
        components: [planeMesh,transformFloor,material,floorBodyInfo]
    }



}
