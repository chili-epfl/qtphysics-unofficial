#ifndef PHYSICSBODYINFOBACKENDNODE_H
#define PHYSICSBODYINFOBACKENDNODE_H

#include "qtphysicsunofficial_global.h"

#include "../physicscollision.h"

namespace Physics {

class PhysicsManager;

/*PhysicsBodyInfoBackendNode: the representation of the node PhysicsBodyInfo in the backend.
PhysicsSoftBodyInfo is handled as a special case*/
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBodyInfoBackendNode : public Qt3DCore::QBackendNode
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
            KinematicChanged = 512,
            EnabledChanged = 1024

    };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    explicit PhysicsBodyInfoBackendNode();
    ~PhysicsBodyInfoBackendNode();

    virtual void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    virtual DirtyFlags& dirtyFlags(){return m_dirtyFlags;}

    virtual QString objectName(){return m_objectName;}

    virtual void setManager(PhysicsManager *manager);

    virtual int mask(){return m_mask;}
    virtual void setMask(int mask);

    virtual int group(){return m_group;}
    virtual void setGroup(int group);

    virtual bool kinematic(){return m_kinematic;}
    virtual void setKinematic(bool kinematic);

    virtual qreal restitution(){return m_restitution;}
    virtual void setRestitution(qreal restitution);

    virtual qreal rollingFriction(){return m_rollingFriction;}
    virtual void setRollingFriction(qreal rollingFriction);

    virtual qreal friction(){return m_friction;}
    virtual void setFriction(qreal friction);

    virtual qreal mass(){return m_mass;}
    virtual void setMass(qreal mass);

    virtual QVector3D fallInertia(){return m_fallInertia;}
    virtual void setFallInertia(QVector3D fallInertia);

    virtual const QVariantMap& shapeDetails(){return m_shapeDetails;}
    virtual void setShapeDetails(QVariantMap shapeDetails);

    virtual Qt3DCore::QNodeId inputTransform(){return m_inputTransform;}
    virtual void setInputTransform(Qt3DCore::QNodeId inputTranform);

    virtual QMatrix4x4 localTransform() {return m_local_transform;}
    virtual void setLocalTransform(QMatrix4x4 m){m_local_transform=m;}

    virtual void notifyFrontEnd(QString operation);

    virtual QHash<Physics::Collision,ushort>& collisions(){return m_collisions;}
    virtual void resetCollisions();

    bool isEnabled(){return m_enabled;}
    void setEnabled(bool val);

protected:
    virtual void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;

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
    Qt3DCore::QNodeId m_inputTransform;

    PhysicsManager* m_manager;

    QHash<Physics::Collision,ushort> m_collisions;

    QMatrix4x4 m_local_transform;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsBodyInfoBackendNode::DirtyFlags)


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBodyInfoBackendNodeFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsBodyInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}

#endif // PHYSICSBODYINFOBACKENDNODE_H
