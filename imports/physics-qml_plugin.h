#ifndef PHYSICS_QML_PLUGIN_H
#define PHYSICS_QML_PLUGIN_H

#include <QQmlExtensionPlugin>

class Qml_PhysicsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // PHYSICS_QML_PLUGIN_H

