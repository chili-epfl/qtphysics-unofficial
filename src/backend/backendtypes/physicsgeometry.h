#ifndef PHYSICSGEOMETRY_H
#define PHYSICSGEOMETRY_H
#include <qtphysicsunofficial_global.h>

namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometry : public Qt3DCore::QBackendNode
{
public:

    explicit PhysicsGeometry();
    ~PhysicsGeometry();

    QString objectName(){return m_objectName;}

    bool isEnabled(){return m_enabled;}
    void setManager(PhysicsManager *manager);
    inline QVector<Qt3DCore::QNodeId> attributes() const { return m_attributes; }
protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_OVERRIDE;
    QString m_objectName;

    bool m_enabled;

    QVector<Qt3DCore::QNodeId> m_attributes;

    PhysicsManager* m_manager;

};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsGeometryFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicsGeometryFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSGEOMETRY_H
