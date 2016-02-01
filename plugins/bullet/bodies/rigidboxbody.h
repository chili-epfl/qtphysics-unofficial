#ifndef RigidBoxBody_H
#define RigidBoxBody_H

#include "abstractrigidbody.h"
#include <QVector3D>

namespace Physics {

namespace Bullet {

class RigidBoxBody: public AbstractRigidBody
{
    Q_OBJECT
public:
    explicit RigidBoxBody(QObject* parent=0);
    ~RigidBoxBody();

    QVector3D dimension(){return m_dimension;}
    void setDimension(QVector3D dimention);
protected:
    virtual void initShape();
private:
    QVector3D m_dimension;

};

}

}
#endif // RigidBoxBody_H
