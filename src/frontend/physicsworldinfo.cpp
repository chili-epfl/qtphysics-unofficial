#include "physicsworldinfo.h"
#include <QVariantList>
#include <Qt3DCore>
#include <Qt3DRenderer>

namespace Physics {


PhysicsWorldInfo::PhysicsWorldInfo(QNode* parent):
    Qt3D::QComponent(parent),
    m_gravity(0, -10, 0)
{

}

PhysicsWorldInfo::~PhysicsWorldInfo(){
    Qt3D::QNode::cleanup();
}

void PhysicsWorldInfo::setGravity(QVector3D gravity){
    if(m_gravity!=gravity){
        m_gravity=gravity;
        emit gravityChanged(m_gravity);
    }
}

void PhysicsWorldInfo::copy(const Qt3D::QNode *ref){
    Qt3D::QComponent::copy(ref);
    const PhysicsWorldInfo* world_info = static_cast<const PhysicsWorldInfo *>(ref);
    m_gravity=world_info->gravity();

}

void PhysicsWorldInfo::sceneChangeEvent(const Qt3D::QSceneChangePtr &change)
{
    Qt3D::QScenePropertyChangePtr e = qSharedPointerCast< Qt3D::QScenePropertyChange>(change);
    if (e->type() == Qt3D::NodeUpdated) {
        if(e->propertyName() == QByteArrayLiteral("debugdraw")){
            Q_FOREACH(QObject* c,this->children()){
                c->deleteLater();
            }
            QVariantList elements= e->value().value<QVariantList>();
            for(int i=0;i<elements.size();i++){
                QVector3D v=elements[i].value<QVector3D>();
                Qt3D::QEntity* entity=new Qt3D::QEntity(this);
                Qt3D::QSphereMesh* sphere_mesh=new Qt3D::QSphereMesh(this);
                sphere_mesh->setRadius(0.5);
                Qt3D::QTransform* transform=new Qt3D::QTransform(this);
                Qt3D::QTranslateTransform* translate=new Qt3D::QTranslateTransform(this);
                translate->setDx(v.x());translate->setDy(v.y());translate->setDz(v.z());
                transform->addTransform(translate);
                entity->addComponent(sphere_mesh);
                entity->addComponent(transform);
            }
        }
    }
}
}


