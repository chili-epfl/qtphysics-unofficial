#ifndef ABSTRACTCOLLITIONSHAPE_H
#define ABSTRACTCOLLITIONSHAPE_H

#include <QQuickItem>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>



namespace Bullet {

class World;

class AbstractCollitionShape : public QQuickItem
{
    Q_OBJECT
public:
    AbstractCollitionShape(QQuickItem* parent=0);
    void setWorld(World* world);
signals:

public slots:

protected:
    virtual void clean()=0;

    btCollisionShape* m_shape ;
    btDefaultMotionState* m_motionState;
    btRigidBody::btRigidBodyConstructionInfo* m_rigidBodyCI;
    btRigidBody* m_rigidBody;
    World* m_world;
};

}
#endif // ABSTRACTCOLLITIONSHAPE_H
