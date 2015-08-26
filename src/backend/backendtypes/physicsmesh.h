#ifndef PHYSICSMESH_H
#define PHYSICSMESH_H
#include "backend_global.h"
#include <Qt3DCore>
#include <Qt3DRenderer>
#include "jobs/updatephysicsentitiesjob.h"


namespace Physics {

class PhysicsManager;
class BACKENDSHARED_EXPORT PhysicsMesh : public Qt3D::QBackendNode
{
public:
    enum Mesh_Type{SPHERE, CUBOID, GENERAL};

    explicit PhysicsMesh();
    ~PhysicsMesh();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setManager(PhysicsManager *manager);

protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void setMeshFunctor(Qt3D::QAbstractMeshFunctorPtr functor);

    QString m_objectName;

    bool m_dirty;
    bool m_enabled;

    Qt3D::QAbstractMeshFunctorPtr m_meshfunctor;

    PhysicsManager* m_manager;
    Mesh_Type m_type;

    /*Variables for specifics mesh types*/
    qreal m_radius;
    qreal m_x_dim,m_y_dim,m_z_dim;

friend class UpdatePhysicsEntitiesJob;
};


class BACKENDSHARED_EXPORT PhysicsMeshFunctor : public Qt3D::QBackendNodeFunctor
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


#endif // PHYSICSMESH_H
