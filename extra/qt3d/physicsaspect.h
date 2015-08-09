#ifndef PhysicsASPECT_H
#define PhysicsASPECT_H

#include <Qt3DCore/QAbstractAspect>


QT_BEGIN_NAMESPACE

namespace Physics {

class PhysicsManager;

class PhysicsAspect: public Qt3D::QAbstractAspect
{
public:
    explicit PhysicsAspect(QObject* parent=0);

    QVector<Qt3D::QAspectJobPtr> jobsToExecute(qint64 time) Q_DECL_OVERRIDE;
    void sceneNodeAdded(Qt3D::QSceneChangePtr &e) Q_DECL_OVERRIDE;
    void sceneNodeRemoved(Qt3D::QSceneChangePtr &e) Q_DECL_OVERRIDE;

private:
    void setRootEntity(Qt3D::QEntity *rootObject) Q_DECL_OVERRIDE;
    void onInitialize(const QVariantMap &data) Q_DECL_OVERRIDE;
    void onCleanup() Q_DECL_OVERRIDE;
    void visitNode(Qt3D::QNode *node);

    PhysicsManager* m_manager;

signals:

public slots:
};
}
QT_END_NAMESPACE

#endif // PhysicsASPECT_H
