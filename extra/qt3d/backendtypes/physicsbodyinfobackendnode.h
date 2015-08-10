#ifndef PHYSICSBODYINFOBACKENDNODE_H
#define PHYSICSBODYINFOBACKENDNODE_H

#include <Qt3DCore>
#include <Qt3DRenderer>

QT_BEGIN_NAMESPACE

namespace Physics {

class PhysicsManager;
class PhysicsBodyInfoBackendNode : public Qt3D::QBackendNode
{
public:
    enum DirtyFlag {
            Clean,
            MaskChanged,
            GroupChanged,
            MassChanged,
            FallInertiaChanged,
            RestistutionChanged,
            FrictionChanged,
            RollingFrictionChanged
        };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    PhysicsBodyInfoBackendNode();
    ~PhysicsBodyInfoBackendNode();
    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    void setManager(PhysicsManager *manager);
    PhysicsManager* manager();

    void setMask(int mask);
    void setGroup(int group);
    void setRestitution(qreal restitution);
    void setRollingFriction(qreal rollingFriction);
    void setFriction(qreal friction);
    void setMass(qreal mass);
    void setFallInertia(QVector3D fallInertia);

    void notifyFrontEnd();
protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_enabled;
    DirtyFlags m_dirtyFlags;

    int m_mask;
    int m_group;
    qreal m_mass;
    QVector3D m_fallInertia;
    qreal m_restitution;
    qreal m_friction;
    qreal m_rollingFriction;

    PhysicsManager* m_manager;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsBodyInfoBackendNode::DirtyFlags)

class PhysicsBodyInfoBackendNodeFunctor : public Qt3D::QBackendNodeFunctor
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

QT_END_NAMESPACE

#endif // PHYSICSBODYINFOBACKENDNODE_H
