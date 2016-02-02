#ifndef PHYSICSTRANSFORM_H
#define PHYSICSTRANSFORM_H
#include <qtphysicsunofficial_global.h>

namespace Physics {

class PhysicsManager;

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsTransform : public Qt3DCore::QBackendNode
{
public:
    explicit PhysicsTransform();
    ~PhysicsTransform();
    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){ m_dirty=dirty;}
    bool isEnabled(){return m_enabled;}

    void setManager(PhysicsManager *manager);

    const QMatrix4x4& transformMatrix(){return m_transformMatrix;}

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_dirty;
    bool m_enabled;
    QMatrix4x4 m_transformMatrix;
    QQuaternion m_rotation;
    QVector3D m_scale;
    QVector3D m_translation;
    PhysicsManager* m_manager;

    void updateMatrix();
};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsTransformFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsTransformFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;

};

}

#endif // PHYSICSTRANSFORM_H
