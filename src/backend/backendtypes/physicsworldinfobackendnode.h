#ifndef PHYSICSWORLDINFOBACKENDNODE_H
#define PHYSICSWORLDINFOBACKENDNODE_H


#include <qtphysicsunofficial_global.h>


namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsWorldInfoBackendNode : public Qt3DCore::QBackendNode
{
public:
    enum DirtyFlag {
            Clean = 0 ,
            GravityChanged = 1,
            EnableChanged = 2
        };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    explicit PhysicsWorldInfoBackendNode();
    ~PhysicsWorldInfoBackendNode();

    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    DirtyFlags& dirtyFlags(){return m_dirtyFlags;}

    QString objectName(){return m_objectName;}

    void setManager(PhysicsManager *manager);

    void setGravity(QVector3D gravity);

    QVector3D gravity(){return m_gravity;}
    bool debug(){return m_debug;}

    void notifyFrontEnd(QString operation, QVariantList args);

    bool isEnabled(){return m_enabled;}
    void setEnabled(bool val);

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    DirtyFlags m_dirtyFlags;

    QString m_objectName;

    bool m_enabled;

    QVector3D m_gravity;
    bool m_debug;

    PhysicsManager* m_manager;


};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsWorldInfoBackendNode::DirtyFlags)

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsWorldInfoBackendNodeFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsWorldInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}


#endif // PHYSICSWORLDINFOBACKENDNODE_H
