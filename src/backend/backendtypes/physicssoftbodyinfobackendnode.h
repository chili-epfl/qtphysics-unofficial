#ifndef PHYSICSSOFTBODYINFOBACKENDNODE_H
#define PHYSICSSOFTBODYINFOBACKENDNODE_H

#include "physicsbodyinfobackendnode.h"
#include "physicssoftbodyinfo.h"

namespace Physics {


class BACKENDSHARED_EXPORT PhysicsSoftBodyInfoBackendNode: public PhysicsBodyInfoBackendNode
{
public:

    explicit PhysicsSoftBodyInfoBackendNode();
    ~PhysicsSoftBodyInfoBackendNode();
    virtual void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    Qt3D::QNodeId inputMesh(){return m_inputMesh;}
    void setInputMesh(Qt3D::QNodeId inputMesh);

    bool isDirtyMesh(){return m_dirtyMesh;}
    void setDirtyMesh(bool val){m_dirtyMesh=val;}

protected:
    virtual void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;

    bool m_dirtyMesh;

    Qt3D::QNodeId m_inputMesh;



};

class BACKENDSHARED_EXPORT PhysicsSoftBodyInfoBackendNodeFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsSoftBodyInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};



}
#endif // PHYSICSSOFTBODYINFOBACKENDNODE_H
