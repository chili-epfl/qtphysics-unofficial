import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import ch.epfl.bulletqml 1.0 as Bullet

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    property real h:20;

    Bullet.World{
        id:world
    }

    Bullet.Sphere{
        id:sphere
        objectName: "Sphere"
        world:world
        restitution:0.9
        friction:10
        rollingFriction:1
        transformation: Qt.matrix4x4(1,0,0,0,0,1,0,h,0,0,1,0,0,0,0,1);
        onTransformationFromBulletChanged: {
            console.log(m.m14,m.m24)
            button.y=parent.height*(h-m.m24)/20
            button.x=(m.m14)*10
        }
    }
    Bullet.HeightField2D{
        id:ground
        objectName: "Ground"
        restitution:0.6
        friction:10
        rollingFriction:1
        world:world
    }

    Button{
        id:button
        text: "Start"
        onClicked: {
            text="I'm a ball!!!"
            sphere.applyImpulse(Qt.vector3d(5,0,0));
            world.start()
        }
    }




}
