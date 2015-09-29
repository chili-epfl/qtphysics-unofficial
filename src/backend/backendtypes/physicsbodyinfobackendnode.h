#ifndef PHYSICSBODYINFOBACKENDNODE_H
#define PHYSICSBODYINFOBACKENDNODE_H

#include "backend_global.h"

#include <Qt3DCore>
#include <Qt3DRenderer>

namespace Physics {

class PhysicsManager;

/*PhysicsBodyInfoBackendNode: the representation of the node PhysicsBodyInfo in the backend*/
class BACKENDSHARED_EXPORT PhysicsBodyInfoBackendNode : public Qt3D::QBackendNode
{
public:
    enum DirtyFlag {
            Clean = 0,
            MaskChanged = 1 ,
            GroupChanged = 2,
            MassChanged = 4,
            FallInertiaChanged = 8,
            RestistutionChanged = 16,
            FrictionChanged = 32,
            RollingFrictionChanged = 64,
            ShapeDetailsChanged = 128,
            InputTransformChanged = 256,
            KinematicChanged = 512
        };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    explicit PhysicsBodyInfoBackendNode();
    ~PhysicsBodyInfoBackendNode();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    DirtyFlags& dirtyFlags(){return m_dirtyFlags;}

    QString objectName(){return m_objectName;}

    void setManager(PhysicsManager *manager);

    int mask(){return m_mask;}
    void setMask(int mask);

    int group(){return m_group;}
    void setGroup(int group);

    bool kinematic(){return m_kinematic;}
    void setKinematic(bool kinematic);

    qreal restitution(){return m_restitution;}
    void setRestitution(qreal restitution);

    qreal rollingFriction(){return m_rollingFriction;}
    void setRollingFriction(qreal rollingFriction);

    qreal friction(){return m_friction;}
    void setFriction(qreal friction);

    qreal mass(){return m_mass;}
    void setMass(qreal mass);

    QVector3D fallInertia(){return m_fallInertia;}
    void setFallInertia(QVector3D fallInertia);

    const QVariantMap& shapeDetails(){return m_shapeDetails;}
    void setShapeDetails(QVariantMap shapeDetails);

    Qt3D::QNodeId inputTransform(){return m_inputTransform;}
    void setInputTransform(Qt3D::QNodeId inputTranform);

    void notifyFrontEnd(QString operation, QVariantMap args);
protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;

private:
    DirtyFlags m_dirtyFlags;

    QString m_objectName;
    bool m_enabled;

    int m_mask;
    int m_group;
    bool m_kinematic;

    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;

    QVariantMap m_shapeDetails;
    Qt3D::QNodeId m_inputTransform;

    PhysicsManager* m_manager;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsBodyInfoBackendNode::DirtyFlags)


class BACKENDSHARED_EXPORT PhysicsBodyInfoBackendNodeFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsBodyInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}

#endif // PHYSICSBODYINFOBACKENDNODE_H
