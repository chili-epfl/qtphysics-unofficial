#ifndef PhysicsENTITY_H
#define PhysicsENTITY_H
#include "backend_global.h"

#include <Qt3DCore>


namespace Physics {

class PhysicsManager;
class  BACKENDSHARED_EXPORT PhysicsEntity : public Qt3D::QBackendNode
{
public:
    explicit PhysicsEntity();
    ~PhysicsEntity();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    PhysicsEntity* parent();
    Qt3D::QNodeId parentId()  { return m_parentId; }

    void addChildId(Qt3D::QNodeId childId);
    void removeChildId(Qt3D::QNodeId childId);

    const QSet<Qt3D::QNodeId>& childrenIds()  { return m_childrenId; }

    void setParentEntity(Qt3D::QEntity* parent);

    void addComponent(Qt3D::QComponent* comp);
    void removeComponent(Qt3D::QNodeId componentId);

    void setManager(PhysicsManager *manager);

    Qt3D::QNodeId physics_transform(){return m_physics_transform;}
    Qt3D::QNodeId abstractmesh(){return m_abstractmesh;}
    Qt3D::QNodeId default_transform(){return m_default_transform;}
    Qt3D::QNodeId physicsBodyInfo(){return m_physicsBodyInfo;}
    Qt3D::QNodeId physicsWorldInfo(){return m_physicsWorldInfo;}


protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:

    Qt3D::QNodeId m_parentId;
    QSet<Qt3D::QNodeId > m_childrenId;

    QString m_objectName;

    Qt3D::QNodeId m_default_transform;
    Qt3D::QNodeId m_physics_transform;
    Qt3D::QNodeId m_abstractmesh;
    Qt3D::QNodeId m_physicsBodyInfo;

    Qt3D::QNodeId m_physicsWorldInfo;

    PhysicsManager* m_manager;

};


class BACKENDSHARED_EXPORT  PhysicsEntityFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsEntityFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}



#endif // PhysicsENTITYFUNCTOR_H
