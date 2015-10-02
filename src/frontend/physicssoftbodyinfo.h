#ifndef PHYSICSSOFTBODYINFO_H
#define PHYSICSSOFTBODYINFO_H

#include "physicsbodyinfo.h"
#include <Qt3DRenderer/QGeometryRenderer>

namespace Physics {



class FRONTENDSHARED_EXPORT PhysicsSoftBodyInfo: public PhysicsBodyInfo
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QGeometryRenderer* inputMesh READ inputMesh WRITE setInputMesh NOTIFY inputMeshChanged)
    Q_PROPERTY(Qt3D::QGeometryRenderer* outputMesh READ outputMesh NOTIFY outputMeshChanged)
public:
    explicit PhysicsSoftBodyInfo(Qt3D::QNode* parent=0);
    ~PhysicsSoftBodyInfo();
    Qt3D::QGeometryRenderer* inputMesh(){return m_inputMesh;}
    Qt3D::QGeometryRenderer* outputMesh(){return m_outputMesh;}

    void setInputMesh(Qt3D::QGeometryRenderer* mesh);

signals:
    void inputMeshChanged();
    void outputMeshChanged();

protected:
    void copy(const Qt3D::QNode *ref) Q_DECL_OVERRIDE;
    QT3D_CLONEABLE(PhysicsSoftBodyInfo)

    Qt3D::QGeometryRenderer* m_inputMesh;
    Qt3D::QGeometryRenderer* m_outputMesh;

};

}
#endif // PHYSICSSOFTBODYINFO_H
