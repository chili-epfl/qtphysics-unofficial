
import Qt3D 2.0
import Qt3D.Renderer 2.0
import ch.epfl.bulletqml 1.0
import QtQuick 2.0 as QQ2


Entity {
    property alias test: test
    id: sceneRoot
    objectName: "Root"
    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, -40.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    Configuration  {
        controlledCamera: camera
    }

    components: [
        FrameGraph {
            activeFrameGraph: Viewport {
                id: viewport
                rect: Qt.rect(0.0, 0.0, 1.0, 1.0) // From Top Left
                clearColor: Qt.rgba(0, 0.5, 1, 1)

                CameraSelector {
                    id : cameraSelector
                    camera: camera

                    ClearBuffer {
                        buffers : ClearBuffer.ColorDepthBuffer
                    }
                }
            }
        }
    ]

    PhongMaterial {
        id: material
    }

    TorusMesh {
        id: torusMesh
        radius: 5
        minorRadius: 1
        rings: 100
        slices: 20
    }

    Transform {
        id: torusTransform
        /*Scale { scale3D: Qt.vector3d(1.5, 1, 0.5) }
        Rotate {
            angle: 45
            axis: Qt.vector3d(1, 0, 0)
        }*/
    }
    PhysicsBodyInfo{
        id:test
        mass:1
    }
    Entity {
        id: torusEntity
        components: [ torusMesh, material, torusTransform,test ]
    }

    SphereMesh {
        id: sphereMesh
        radius: 3
    }

    Transform {
        id: sphereTransform
        Translate {
            translation: Qt.vector3d(20, 0, 0)
        }

        Rotate {
            id: sphereRotation
            axis: Qt.vector3d(0, 1, 0)
        }
    }

    Entity {
        objectName: "Sphere"
        id: sphereEntity
        components: [ sphereMesh, material, sphereTransform ]
    }
}
