#include "abstractcollitionshape.h"
#include "world.h"
Bullet::AbstractCollitionShape::AbstractCollitionShape(QQuickItem* parent):QQuickItem(parent)
{
    m_world=NULL;

}

void Bullet::AbstractCollitionShape::setWorld(World* world){
    m_world=world;
    m_world->addRigidBody(m_rigidBody);
}

