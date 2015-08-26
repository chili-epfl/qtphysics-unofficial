#ifndef PHYSICSWORLDINFOBACKENDNODE_H
#define PHYSICSWORLDINFOBACKENDNODE_H


#include "backend_global.h"

#include <Qt3DCore>
#include <Qt3DRenderer>

namespace Physics {

class PhysicsManager;
class BACKENDSHARED_EXPORT PhysicsWorldInfoBackendNode : public Qt3D::QBackendNode
{
public:
    enum DirtyFlag {
            Clean = 0 ,
            GravityChanged = 1
        };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    explicit PhysicsWorldInfoBackendNode();
    ~PhysicsWorldInfoBackendNode();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    DirtyFlags& dirtyFlags(){return m_dirtyFlags;}

    QString objectName(){return m_objectName;}

    void setManager(PhysicsManager *manager);

    void setGravity(QVector3D gravity);

    QVector3D gravity(){return m_gravity;}
protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    DirtyFlags m_dirtyFlags;

    QString m_objectName;

    bool m_enabled;

    QVector3D m_gravity;

    PhysicsManager* m_manager;


};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsWorldInfoBackendNode::DirtyFlags)

class BACKENDSHARED_EXPORT PhysicsWorldInfoBackendNodeFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsWorldInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}


#endif // PHYSICSWORLDINFOBACKENDNODE_H
