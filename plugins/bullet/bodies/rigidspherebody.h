#ifndef RigidSphereBody_H
#define RigidSphereBody_H

#include <bodies/abstractrigidbody.h>

namespace Physics {


namespace Bullet {

class RigidSphereBody: public AbstractRigidBody
{
    Q_OBJECT

public:
    explicit RigidSphereBody(QObject* parent=0);
    ~RigidSphereBody();
    qreal radius(){return m_radius;}
    void setRadius(qreal radius);
protected:
    virtual void initShape();

private:

    qreal m_radius;
};

}}
#endif // RigidSphereBody_H
