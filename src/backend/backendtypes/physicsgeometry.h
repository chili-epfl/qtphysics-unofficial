#ifndef PHYSICSGEOMETRY_H
#define PHYSICSGEOMETRY_H
#include "backend_global.h"
#include <Qt3DCore>
#include <Qt3DRenderer>
#include "jobs/debugjob.h"

namespace Physics {

class PhysicsManager;
class BACKENDSHARED_EXPORT PhysicsGeometry : public Qt3D::QBackendNode
{
public:

    explicit PhysicsGeometry();
    ~PhysicsGeometry();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);
    inline int verticesPerPatch() const { return m_verticesPerPatch; }
    inline QVector<Qt3D::QNodeId> attributes() const { return m_attributes; }
protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_dirty;
    bool m_enabled;

    QVector<Qt3D::QNodeId> m_attributes;
    int m_verticesPerPatch;

    PhysicsManager* m_manager;

    friend class DebugJob;


};


class BACKENDSHARED_EXPORT PhysicsGeometryFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsGeometryFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSGEOMETRY_H
