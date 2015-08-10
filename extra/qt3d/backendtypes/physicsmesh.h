#ifndef PHYSICSMESH_H
#define PHYSICSMESH_H

#include <Qt3DCore>
#include <Qt3DRenderer>

QT_BEGIN_NAMESPACE

namespace Physics {

class PhysicsManager;
class PhysicsMesh : public Qt3D::QBackendNode
{
public:
    PhysicsMesh();
    ~PhysicsMesh();
    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    void setManager(PhysicsManager *manager);
    PhysicsManager* manager();
protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void setMeshFunctor(Qt3D::QAbstractMeshFunctorPtr functor);
    QString m_objectName;

    bool m_dirty;
    bool m_enabled;
    Qt3D::QAbstractMeshFunctorPtr m_meshfunctor;
    PhysicsManager* m_manager;

};


class PhysicsMeshFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsMeshFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

QT_END_NAMESPACE

#endif // PHYSICSMESH_H
