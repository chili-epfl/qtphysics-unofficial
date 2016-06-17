#ifndef PHYSICSBUFFER_H
#define PHYSICSBUFFER_H

#include <qtphysicsunofficial_global.h>

#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QBufferDataGenerator>

namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBuffer : public Qt3DCore::QBackendNode
{
public:

    explicit PhysicsBuffer();
    ~PhysicsBuffer();

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);
    bool isEnabled(){return m_enabled;}

    inline Qt3DRender::QBuffer::BufferType type() const { return m_type; }
    inline Qt3DRender::QBuffer::UsageType usage() const { return m_usage; }
    inline QByteArray data() const { return m_data; }
    inline Qt3DRender::QBufferDataGeneratorPtr bufferFunctor() const { return m_functor; }

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_FINAL;

    QString m_objectName;
    bool m_enabled;

    bool m_dirty;

    Qt3DRender::QBuffer::BufferType m_type;
    Qt3DRender::QBuffer::UsageType m_usage;
    QByteArray m_data;
    Qt3DRender::QBufferDataGeneratorPtr  m_functor;

    PhysicsManager* m_manager;


};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsBufferFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicsBufferFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSBUFFER_H
