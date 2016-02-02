#ifndef RigidStaticPlaneBody_H
#define RigidStaticPlaneBody_H

#include <bodies/abstractrigidbody.h>
#include <QVector3D>

namespace Physics {

namespace Bullet {

class RigidStaticPlaneBody : public AbstractRigidBody
{
    Q_OBJECT
public:
    explicit RigidStaticPlaneBody(QObject* parent=0);
    ~RigidStaticPlaneBody();
    QVector3D normal(){return m_normal;}
    void setNormal(QVector3D normal);
    qreal planeConstant(){return m_planeConstant;}
    void setPlaneConstant(qreal d);
    virtual void setMass(qreal m) Q_DECL_OVERRIDE;

public slots:

protected:
        void initShape();
private:

    QVector3D m_normal;
    qreal m_planeConstant;
};

}
}
#endif // RigidStaticPlaneBody_H
