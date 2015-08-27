#ifndef PhysicsWorldInfo_H
#define PhysicsWorldInfo_H
#include "frontend_global.h"

#include <Qt3DCore/QComponent>
#include <QVector3D>

namespace Physics {


class FRONTENDSHARED_EXPORT PhysicsWorldInfo:
        public Qt3D::QComponent
{
    Q_OBJECT
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity NOTIFY gravityChanged)

public:
    explicit PhysicsWorldInfo(QNode* parent=0);
    ~PhysicsWorldInfo();
    void copy(const QNode *ref) Q_DECL_OVERRIDE;

    QVector3D gravity() const {return m_gravity;}
    void setGravity(QVector3D gravity);
signals:
    void gravityChanged(QVector3D gravity);
private:
    QVector3D m_gravity;

    QT3D_CLONEABLE(PhysicsWorldInfo)

};

}
#endif // PhysicsWorldInfo_H
