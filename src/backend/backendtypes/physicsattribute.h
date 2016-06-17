#ifndef PHYSICSATTRIBUTE_H
#define PHYSICSATTRIBUTE_H

#include <qtphysicsunofficial_global.h>

namespace Physics {

class PhysicsManager;
class QTPHYSICSUNOFFICIAL_EXPORT PhysicsAttribute : public Qt3DCore::QBackendNode
{
public:

    explicit PhysicsAttribute();
    ~PhysicsAttribute();
    QString objectName(){return m_objectName;}

    bool isDirty(){return m_dirty;}
    void setDirty(bool dirty){m_dirty=dirty;}
    void setManager(PhysicsManager *manager);

    inline Qt3DCore::QNodeId bufferId() const { return m_bufferId; }
    inline Qt3DRender::QAttribute::VertexBaseType dataType() const { return m_dataType; }
    inline uint dataSize() const { return m_dataSize; }
    inline uint count() const { return m_count; }
    inline uint byteStride() const { return m_byteStride; }
    inline uint byteOffset() const { return m_byteOffset; }
    inline uint divisor() const { return m_divisor; }
    bool isEnabled(){return m_enabled;}
    inline Qt3DRender::QAttribute::AttributeType attributeType() const { return m_attributeType; }
    QVector<QVector3D> asVector3D() const;
protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_FINAL;

    Qt3DCore::QNodeId m_bufferId;
    Qt3DRender::QAttribute::VertexBaseType m_dataType;
    /*These can make dirty true*/
    uint m_dataSize;
    uint m_count;
    uint m_byteStride;
    uint m_byteOffset;
    uint m_divisor;
    QString m_objectName;
    bool m_dirty;


    bool m_enabled;
    Qt3DRender::QAttribute::AttributeType m_attributeType;

    PhysicsManager* m_manager;


};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsAttributeFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicsAttributeFunctor(PhysicsManager* manager);
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_OVERRIDE;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_OVERRIDE;
private:
    PhysicsManager* m_manager;


};

}

#endif // PHYSICSATTRIBUTE_H
