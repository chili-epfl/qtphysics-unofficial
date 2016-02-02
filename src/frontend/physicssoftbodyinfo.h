#ifndef PHYSICSSOFTBODYINFO_H
#define PHYSICSSOFTBODYINFO_H

#include <frontend/physicsbodyinfo.h>

namespace Physics {



class QTPHYSICSUNOFFICIAL_EXPORT PhysicsSoftBodyInfo: public PhysicsBodyInfo
{
    Q_OBJECT
    Q_PROPERTY(Qt3DRender::QGeometryRenderer* inputMesh READ inputMesh WRITE setInputMesh NOTIFY inputMeshChanged)
    Q_PROPERTY(Qt3DRender::QGeometryRenderer* outputMesh READ outputMesh NOTIFY outputMeshChanged)
public:
    explicit PhysicsSoftBodyInfo(Qt3DCore::QNode* parent=0);
    ~PhysicsSoftBodyInfo();
    Qt3DRender::QGeometryRenderer* inputMesh(){return m_inputMesh;}
    Qt3DRender::QGeometryRenderer* outputMesh(){return m_outputMesh;}

    void setInputMesh(Qt3DRender::QGeometryRenderer* mesh);

signals:
    void inputMeshChanged();
    void outputMeshChanged();

protected:
    void copy(const Qt3DCore::QNode *ref) Q_DECL_OVERRIDE;
    QT3D_CLONEABLE(PhysicsSoftBodyInfo)

    Qt3DRender::QGeometryRenderer* m_inputMesh;
    Qt3DRender::QGeometryRenderer* m_outputMesh;

};

}
#endif // PHYSICSSOFTBODYINFO_H
