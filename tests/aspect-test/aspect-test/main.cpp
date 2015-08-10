#include <QGuiApplication>
#include <QQuickView>
#include <QLibrary>
#include <QDebug>
#include <Qt3DCore/qaspectengine.h>
int main(int argc, char **argv)
{
    /*QLibrary library("/home/lorenzo/qt5/build-linux/qtbase/lib/libPhysics");
    if (!library.load())
    qDebug() << library.errorString();
    if (library.load())
    qDebug() << "library loaded";*/

    /*Qt3D::QAspectEngine engine;
    engine.registerAspect(new);*/

    QGuiApplication app(argc, argv);

    QQuickView view;

    view.resize(500, 500);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
