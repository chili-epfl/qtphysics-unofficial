#include <QGuiApplication>
#include <QQuickView>
#include <QLibrary>
#include <QDebug>
#include <QQmlApplicationEngine>
//#include "physicssetter.h"

#include <Qt3DCore/qaspectengine.h>
int main(int argc, char **argv)
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    //qmlRegisterType<PhysicsSetter>("PhysicsSetter", 1, 0, "PhysicsSetter");

    QQuickView view;

    view.resize(500, 500);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
