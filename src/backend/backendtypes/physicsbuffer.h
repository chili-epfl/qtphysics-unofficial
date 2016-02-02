#ifndef PHYSICSBUFFER_H
#define PHYSICSBUFFER_H

#include <qtphysicsunofficial_global.h>
namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBuffer : public Qt3DCore::QBackendNode
{
public:

    explicit PhysicsBuffer();
    ~PhysicsBuffer();

    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);
    bool isEnabled(){return m_enabled;}

    inline Qt3DRender::QBuffer::BufferType type() const { return m_type; }
    inline Qt3DRender::QBuffer::UsageType usage() const { return m_usage; }
    inline QByteArray data() const { return m_data; }
    inline Qt3DRender::QBufferFunctorPtr bufferFunctor() const { return m_functor; }

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;
    bool m_enabled;

    bool m_dirty;

    Qt3DRender::QBuffer::BufferType m_type;
    Qt3DRender::QBuffer::UsageType m_usage;
    QByteArray m_data;
    Qt3DRender::QBufferFunctorPtr m_functor;

    PhysicsManager* m_manager;


};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBufferFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsBufferFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSBUFFER_H
