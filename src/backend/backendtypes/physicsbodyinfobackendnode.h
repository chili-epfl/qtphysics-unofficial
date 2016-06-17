#ifndef PHYSICSBODYINFOBACKENDNODE_H
#define PHYSICSBODYINFOBACKENDNODE_H

#include <qtphysicsunofficial_global.h>
#include <backend/physicscollision.h>

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
            InputTransformChanged = 128,
            KinematicChanged = 256
    };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    explicit PhysicsBodyInfoBackendNode();
    ~PhysicsBodyInfoBackendNode();

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
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_OVERRIDE;
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

    Qt3DCore::QNodeId m_inputTransform;

    PhysicsManager* m_manager;

    QHash<Physics::Collision,ushort> m_collisions;

    QMatrix4x4 m_local_transform;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsBodyInfoBackendNode::DirtyFlags)


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBodyInfoBackendNodeFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicsBodyInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}

#endif // PHYSICSBODYINFOBACKENDNODE_H
