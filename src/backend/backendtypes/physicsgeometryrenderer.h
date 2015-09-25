#ifndef PhysicsGeometryRenderer_H
#define PhysicsGeometryRenderer_H
#include "backend_global.h"
#include <Qt3DCore>
#include <Qt3DRenderer>
#include "jobs/updatephysicsentitiesjob.h"
#include "jobs/debugjob.h"


namespace Physics {

class PhysicsManager;
class BACKENDSHARED_EXPORT PhysicsGeometryRenderer : public Qt3D::QBackendNode
{
public:
    enum Mesh_Type{SPHERE, CUBOID, GENERAL};

    explicit PhysicsGeometryRenderer();
    ~PhysicsGeometryRenderer();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);

protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void setGeometry(Qt3D::QNodeId geometry);

    QString m_objectName;

    bool m_dirty;
    bool m_enabled;

    Qt3D::QNodeId m_geometry;
    Qt3D::QGeometryFunctorPtr m_geometry_functor;

    PhysicsManager* m_manager;
    Mesh_Type m_type;

    /*Variables for specifics mesh types: not the right place...*/
    qreal m_radius;
    qreal m_x_dim,m_y_dim,m_z_dim;

friend class UpdatePhysicsEntitiesJob;
friend class DebugJob;

};


class BACKENDSHARED_EXPORT PhysicsGeometryRendererFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsGeometryRendererFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}


#endif // PhysicsGeometryRenderer_H
