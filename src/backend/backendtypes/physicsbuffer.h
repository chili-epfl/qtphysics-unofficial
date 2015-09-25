#ifndef PHYSICSBUFFER_H
#define PHYSICSBUFFER_H

#include "backend_global.h"

#include <Qt3DCore>
#include <Qt3DRenderer>

namespace Physics {

class PhysicsManager;
class BACKENDSHARED_EXPORT PhysicsBuffer : public Qt3D::QBackendNode
{
public:

    explicit PhysicsBuffer();
    ~PhysicsBuffer();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);

    inline Qt3D::QBuffer::BufferType type() const { return m_type; }
    inline Qt3D::QBuffer::UsageType usage() const { return m_usage; }
    inline QByteArray data() const { return m_data; }
    inline Qt3D::QBufferFunctorPtr bufferFunctor() const { return m_functor; }

protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_dirty;

    Qt3D::QBuffer::BufferType m_type;
    Qt3D::QBuffer::UsageType m_usage;
    QByteArray m_data;
    Qt3D::QBufferFunctorPtr m_functor;

    PhysicsManager* m_manager;


};


class BACKENDSHARED_EXPORT PhysicsBufferFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit PhysicsBufferFunctor(PhysicsManager* manager);
    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSBUFFER_H
