#ifndef PHYSICSATTRIBUTE_H
#define PHYSICSATTRIBUTE_H

#include "backend_global.h"

namespace Physics {

class PhysicsManager;
class BACKENDSHARED_EXPORT PhysicsAttribute : public Qt3DCore::QBackendNode
{
public:

    explicit PhysicsAttribute();
    ~PhysicsAttribute();

    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;

    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);

    inline Qt3DCore::QNodeId bufferId() const { return m_bufferId; }
    inline Qt3DRender::QAbstractAttribute::DataType dataType() const { return m_dataType; }
    inline uint dataSize() const { return m_dataSize; }
    inline uint count() const { return m_count; }
    inline uint byteStride() const { return m_byteStride; }
    inline uint byteOffset() const { return m_byteOffset; }
    inline uint divisor() const { return m_divisor; }
    inline Qt3DRender::QAbstractAttribute::AttributeType attributeType() const { return m_attributeType; }
    QVector<QVector3D> asVector3D() const;
protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    QString m_objectName;

    bool m_dirty;

    Qt3DCore::QNodeId m_bufferId;
    Qt3DRender::QAbstractAttribute::DataType m_dataType;
    uint m_dataSize;
    uint m_count;
    uint m_byteStride;
    uint m_byteOffset;
    uint m_divisor;
    Qt3DRender::QAbstractAttribute::AttributeType m_attributeType;

    PhysicsManager* m_manager;


};


class BACKENDSHARED_EXPORT PhysicsAttributeFunctor : public Qt3DCore::QBackendNodeFunctor
{
public:
    explicit PhysicsAttributeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend, const Qt3DCore::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3DCore::QNodeId &id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSATTRIBUTE_H
