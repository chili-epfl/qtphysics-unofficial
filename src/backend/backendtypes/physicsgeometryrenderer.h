#ifndef PhysicsGeometryRenderer_H
#define PhysicsGeometryRenderer_H
#include <qtphysicsunofficial_global.h>
#include <backend/jobs/updatephysicsentitiesjob.h>


namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometryRenderer : public Qt3DCore::QBackendNode
{
public:
    explicit PhysicsGeometryRenderer();
    ~PhysicsGeometryRenderer();

    QString objectName(){return m_objectName;}

    bool isEnabled(){return m_enabled;}
    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_FINAL;

    QString m_objectName;

    bool m_dirty;
    bool m_enabled;
    PhysicsManager* m_manager;

    Qt3DCore::QNodeId m_geometry;
    int m_instanceCount;
    int m_vertexCount;
    int m_indexOffset;
    int m_firstInstance;
    int m_firstVertex;
    int m_restartIndexValue;
    int m_verticesPerPatch;
    bool m_primitiveRestartEnabled;
    Qt3DRender::QGeometryRenderer::PrimitiveType m_primitiveType;
    Qt3DRender::QGeometryFactoryPtr m_geometryFactory;

friend class UpdatePhysicsEntitiesJob;

};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometryRendererFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicsGeometryRendererFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}


#endif // PhysicsGeometryRenderer_H
