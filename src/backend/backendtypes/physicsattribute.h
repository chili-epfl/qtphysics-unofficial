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
    bool isEnabled(){return m_enabled;}
    inline Qt3DRender::QAbstractAttribute::AttributeType attributeType() const { return m_attributeType; }
    QVector<QVector3D> asVector3D() const;
protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_OVERRIDE;
private:
    Qt3DCore::QNodeId m_bufferId;
    Qt3DRender::QAbstractAttribute::DataType m_dataType;
    /*These can make dirty true*/
    uint m_dataSize;
    uint m_count;
    uint m_byteStride;
    uint m_byteOffset;
    uint m_divisor;
    QString m_objectName;
    bool m_dirty;


    bool m_enabled;
    Qt3DRender::QAbstractAttribute::AttributeType m_attributeType;

    PhysicsManager* m_manager;


};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsAttributeFunctor : public Qt3DCore::QBackendNodeFunctor
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
