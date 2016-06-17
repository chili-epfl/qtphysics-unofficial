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
            ScaleFactorChanged=2
        };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    explicit PhysicsWorldInfoBackendNode();
    ~PhysicsWorldInfoBackendNode();

    DirtyFlags& dirtyFlags(){return m_dirtyFlags;}

    QString objectName(){return m_objectName;}

    void setManager(PhysicsManager *manager);

    void setGravity(QVector3D gravity);

    void setScaleFactor(qreal val);

    QVector3D gravity(){return m_gravity;}
    bool debug(){return m_debug;}
    qreal scaleFactor(){return m_scaleFactor;}

    void notifyFrontEnd(QString operation, QVariantList args);

    bool isEnabled(){return m_enabled;}
    void setEnabled(bool val);

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_FINAL;

    DirtyFlags m_dirtyFlags;

    QString m_objectName;

    bool m_enabled;

    QVector3D m_gravity;
    qreal m_scaleFactor;
    bool m_debug;

    PhysicsManager* m_manager;


};
Q_DECLARE_OPERATORS_FOR_FLAGS(PhysicsWorldInfoBackendNode::DirtyFlags)

class QTPHYSICSUNOFFICIAL_EXPORT PhysicsWorldInfoBackendNodeFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicsWorldInfoBackendNodeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;
};

}


#endif // PHYSICSWORLDINFOBACKENDNODE_H
