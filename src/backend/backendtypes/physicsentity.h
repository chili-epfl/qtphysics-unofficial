#ifndef PhysicsENTITY_H
#define PhysicsENTITY_H
#include "qtphysicsunofficial_global.h"


namespace Physics {

class PhysicsManager;
class  QTPHYSICSUNOFFICIAL_EXPORT PhysicsEntity : public Qt3DCore::QBackendNode
{
public:
    explicit PhysicsEntity();
    ~PhysicsEntity();

    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    PhysicsEntity* parent();
    Qt3DCore::QNodeId parentId()  { return m_parentId; }

    void addChildId(Qt3DCore::QNodeId childId);
    void removeChildId(Qt3DCore::QNodeId childId);

    const QSet<Qt3DCore::QNodeId>& childrenIds()  { return m_childrenId; }

    void setParentEntity(Qt3DCore::QEntity* parent);

    void addComponent(Qt3DCore::QComponent* comp);
    void removeComponent(Qt3DCore::QNodeId componentId);

    void setManager(PhysicsManager *manager);

    Qt3DCore::QNodeId geometry_renderer(){return m_geometry_renderer;}
    Qt3DCore::QNodeId transform(){return m_transform;}
    Qt3DCore::QNodeId physicsBodyInfo(){return m_physicsBodyInfo;}
    Qt3DCore::QNodeId physicsWorldInfo(){return m_physicsWorldInfo;}
    bool isEnabled(){return m_enabled;}

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:

    Qt3DCore::QNodeId m_parentId;
    QSet<Qt3DCore::QNodeId > m_childrenId;
    bool m_enabled;

    QString m_objectName;

    Qt3DCore::QNodeId m_transform;
    Qt3DCore::QNodeId m_geometry_renderer;
    Qt3DCore::QNodeId m_physicsBodyInfo;

    Qt3DCore::QNodeId m_physicsWorldInfo;

    PhysicsManager* m_manager;

};


class QTPHYSICSUNOFFICIAL_EXPORT  PhysicsEntityFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsEntityFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}



#endif // PhysicsENTITYFUNCTOR_H
