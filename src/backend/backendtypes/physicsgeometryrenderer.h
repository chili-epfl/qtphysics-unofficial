#ifndef PhysicsGeometryRenderer_H
#define PhysicsGeometryRenderer_H
#include <qtphysicsunofficial_global.h>


#include <backend/jobs/updatephysicsentitiesjob.h>
#include <backend/jobs/debugjob.h>


namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometryRenderer : public Qt3DCore::QBackendNode
{
public:
    enum Mesh_Type{SPHERE, CUBOID, GENERAL};

    explicit PhysicsGeometryRenderer();
    ~PhysicsGeometryRenderer();

    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isEnabled(){return m_enabled;}
    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void setGeometry(Qt3DCore::QNodeId geometry);

    QString m_objectName;

    bool m_dirty;
    bool m_enabled;

    Qt3DCore::QNodeId m_geometry;
    Qt3DRender::QGeometryFunctorPtr m_geometry_functor;

    PhysicsManager* m_manager;
    Mesh_Type m_type;

    /*Variables for specifics mesh types: not the right place...*/
    qreal m_radius;
    qreal m_x_dim,m_y_dim,m_z_dim;

friend class UpdatePhysicsEntitiesJob;
friend class DebugJob;

};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometryRendererFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsGeometryRendererFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}


#endif // PhysicsGeometryRenderer_H
