#ifndef PHYSICSTRANSFORM_H
#define PHYSICSTRANSFORM_H
#include "backend_global.h"

#include <Qt3DCore>
#include <Qt3DRenderer>


namespace Physics {

class PhysicsManager;

class BACKENDSHARED_EXPORT PhysicsTransform : public Qt3D::QBackendNode
{
public:
    explicit PhysicsTransform();
    ~PhysicsTransform();
    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){ m_dirty=dirty;}

    void setManager(PhysicsManager *manager);

    const QMatrix4x4& transformMatrix(){return m_transformMatrix;}

protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_dirty;
    bool m_enabled;
    QMatrix4x4 m_transformMatrix;

    PhysicsManager* m_manager;

};


class BACKENDSHARED_EXPORT PhysicsTransformFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsTransformFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSTRANSFORM_H
