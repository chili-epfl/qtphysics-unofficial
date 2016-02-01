#ifndef PHYSICSSOFTBODYINFOBACKENDNODE_H
#define PHYSICSSOFTBODYINFOBACKENDNODE_H

#include "physicsbodyinfobackendnode.h"
#include "physicssoftbodyinfo.h"

namespace Physics {


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsSoftBodyInfoBackendNode: public PhysicsBodyInfoBackendNode
{
public:

    explicit PhysicsSoftBodyInfoBackendNode();
    ~PhysicsSoftBodyInfoBackendNode();
    virtual void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    Qt3DCore::QNodeId inputMesh(){return m_inputMesh;}
    void setInputMesh(Qt3DCore::QNodeId inputMesh);

    bool isDirtyMesh(){return m_dirtyMesh;}
    void setDirtyMesh(bool val){m_dirtyMesh=val;}

protected:
    virtual void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;

    bool m_dirtyMesh;

    Qt3DCore::QNodeId m_inputMesh;



};

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsSoftBodyInfoBackendNodeFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsSoftBodyInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};



}
#endif // PHYSICSSOFTBODYINFOBACKENDNODE_H
