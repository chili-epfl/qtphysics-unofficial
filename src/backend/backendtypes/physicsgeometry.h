#ifndef PHYSICSGEOMETRY_H
#define PHYSICSGEOMETRY_H
#include <qtphysicsunofficial_global.h>

#include <backend/jobs/debugjob.h>

namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometry : public Qt3DCore::QBackendNode
{
public:

    explicit PhysicsGeometry();
    ~PhysicsGeometry();

    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isEnabled(){return m_enabled;}
    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);
    inline int verticesPerPatch() const { return m_verticesPerPatch; }
    inline QVector<Qt3DCore::QNodeId> attributes() const { return m_attributes; }
protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_dirty;
    bool m_enabled;

    QVector<Qt3DCore::QNodeId> m_attributes;
    int m_verticesPerPatch;

    PhysicsManager* m_manager;

    friend class DebugJob;


};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometryFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsGeometryFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSGEOMETRY_H
