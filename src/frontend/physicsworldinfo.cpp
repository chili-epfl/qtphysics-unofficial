#include <frontend/physicsworldinfo.h>
#include <QVariantList>

namespace Physics {


PhysicsWorldInfo::PhysicsWorldInfo(QNode* parent):
    Qt3DCore::QComponent(parent),
    m_gravity(0, -10, 0),
    m_scaleFactor(1)
{

}

PhysicsWorldInfo::~PhysicsWorldInfo()
{
}

void PhysicsWorldInfo::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        emit gravityChanged();
    }
}

void PhysicsWorldInfo::setScaleFactor(qreal val)
{
    if(val!=m_scaleFactor){
        m_scaleFactor=val;
        emit scaleFactorChanged();
    }
}

Qt3DCore::QNodeCreatedChangeBasePtr PhysicsWorldInfo::createNodeCreationChange() const
{
    auto creationChange = Qt3DCore::QNodeCreatedChangePtr<PhysicsWorldInfoData>::create(this);
    PhysicsWorldInfoData &data = creationChange->data;
    data.m_gravity = m_gravity;
    data.m_scaleFactor = m_scaleFactor;
    return creationChange;
}

void PhysicsWorldInfo::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change)
{
    Qt3DCore::QPropertyUpdatedChangePtr e = qSharedPointerCast< Qt3DCore::QPropertyUpdatedChange>(change);
    if (e->type() == Qt3DCore::PropertyUpdated) {

    }
}
}


