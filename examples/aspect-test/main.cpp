#include <QGuiApplication>
#include <QQuickView>
#include <QLibrary>
#include <QDebug>
#include <Qt3DCore/qaspectengine.h>
int main(int argc, char **argv)
{

    QGuiApplication app(argc, argv);

    QQuickView view;

    view.resize(500, 500);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
