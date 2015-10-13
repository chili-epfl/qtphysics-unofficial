#include "physicsbodyinfo.h"
#include <QVariantList>
namespace Physics {

PhysicsBodyInfo::PhysicsBodyInfo(Qt3D::QNode* parent):
    Qt3D::QComponent(parent),
    m_mask(1),
    m_group(1),
    m_kinematic(false),
    m_mass(0),
    m_fallInertia(),
    m_restitution(0.0f),
    m_friction(0.0f),
    m_rollingFriction(0.0f)
{
    m_inputTransform=Q_NULLPTR;
    m_outputTransform=new Qt3D::QTransform(this);
    m_outputTransform_matrix=new Qt3D::QMatrixTransform(m_outputTransform);
    m_outputTransform->addTransform(m_outputTransform_matrix);
    setShareable(false);
}
void PhysicsBodyInfo::copy(const Qt3D::QNode *ref){
    Qt3D::QComponent::copy(ref);
    const PhysicsBodyInfo * body_info = static_cast<const PhysicsBodyInfo *>(ref);

    m_fallInertia=body_info->m_fallInertia;
    m_restitution=body_info->m_restitution;
    m_friction=body_info->m_restitution;
    m_rollingFriction=body_info->m_rollingFriction;
    m_mass=body_info->m_mass;
    m_mask=body_info->m_mask;
    m_group=body_info->m_group;
    m_kinematic=body_info->m_kinematic;

    m_inputTransform=body_info->m_inputTransform;
    m_outputTransform=body_info->m_outputTransform;
    m_outputTransform_matrix=body_info->m_outputTransform_matrix;
}

PhysicsBodyInfo::~PhysicsBodyInfo(){
    Qt3D::QNode::cleanup();
}

void PhysicsBodyInfo::setMass(qreal mass){
    if(mass >=0 && m_mass!=mass){
        m_mass=mass;
        emit massChanged(m_mass);
    }
}
void PhysicsBodyInfo::setShapeDetails(QVariantMap shapeDetails){

   m_shapeDetails=shapeDetails;
   emit shapeDetailsChanged();

}

void PhysicsBodyInfo::setFallInertia(QVector3D fallInertia){
    if( m_fallInertia!=fallInertia){
        m_fallInertia=fallInertia;
        emit fallInertiaChanged(m_fallInertia);
    }
}

void PhysicsBodyInfo::setMask(int mask){
    if(mask >0 && m_mask!=mask){
        m_mask=mask;
        emit maskChanged(m_mask);
    }
}

void PhysicsBodyInfo::setGroup(int group){
    if(group >0 && m_group!=group){
        m_group=group;
        emit groupChanged(m_group);
    }
}
void PhysicsBodyInfo::setKinematic(bool kinematic){
    if(m_kinematic!=kinematic){
        m_kinematic=kinematic;
        emit kinematicChanged(m_kinematic);
    }
}

void PhysicsBodyInfo::setRestitution(qreal restitution){
    if(restitution!=m_restitution){
        m_restitution=restitution;
        emit restitutionChanged(m_restitution);
    }
}

void PhysicsBodyInfo::setRollingFriction(qreal rollingFriction){
    if(rollingFriction!=m_rollingFriction){
        m_rollingFriction=rollingFriction;
        emit rollingFrictionChanged(m_rollingFriction);
    }
}
void PhysicsBodyInfo::setFriction(qreal friction){
    if(friction!=m_friction){
        m_friction=friction;
        emit frictionChanged(m_friction);
    }
}

void PhysicsBodyInfo::setInputTransform(Qt3D::QTransform* inputTransform){
    m_inputTransform=inputTransform;
    emit inputTransformChanged();
}

QQmlListProperty<PhysicsCollisionEvent> PhysicsBodyInfo::collitionsList(){
    return QQmlListProperty<PhysicsCollisionEvent>(this, 0,
                                                 PhysicsBodyInfo::qmlComponentsCount,
                                                 PhysicsBodyInfo::qmlComponentAt);

}

PhysicsCollisionEvent* PhysicsBodyInfo::qmlComponentAt(QQmlListProperty<PhysicsCollisionEvent> *list, int index){
    PhysicsBodyInfo *self = static_cast<PhysicsBodyInfo *>(list->object);
    return self->m_collitionsList.at(index).data();
}

int PhysicsBodyInfo::qmlComponentsCount(QQmlListProperty<PhysicsCollisionEvent> *list){
     PhysicsBodyInfo *self = static_cast<PhysicsBodyInfo *>(list->object);
     return self->m_collitionsList.size();
}


void PhysicsBodyInfo::sceneChangeEvent(const Qt3D::QSceneChangePtr &change)
{
    Qt3D::QScenePropertyChangePtr e = qSharedPointerCast< Qt3D::QScenePropertyChange>(change);
    if (e->type() == Qt3D::NodeUpdated) {
        /*if (e->propertyName() == QByteArrayLiteral("attachPhysicsTransfrom")) {
            bool val = e->value().toBool();
            if(val){
                QVector<Qt3D::QEntity*> entities = this->entities();
                if (entities.size() > 1)
                    qWarning()<< "It is strongly discouraged to share PhysicsBodyInfo component between entities";
                Q_FOREACH(Qt3D::QEntity* e, entities){
                    bool hasPhysicsTransform=false;
                    QMatrix4x4 m;
                    Q_FOREACH(Qt3D::QComponent* c, e->components()){
                        if(c->inherits("Qt3D::QTransform") && c->objectName().compare("@MaDeByPhYsIcS@")!=0){
                            c->setEnabled(false);
                            m=qobject_cast<Qt3D::QTransform*>(c)->matrix();
                        }
                        else if(c->inherits("Qt3D::QTransform") && c->objectName().compare("@MaDeByPhYsIcS@")==0){
                            hasPhysicsTransform=true;
                        }
                    }
                    if(!hasPhysicsTransform){
                        Qt3D::QTransform* physics_transform=new Qt3D::QTransform(this->parentNode());
                        physics_transform->setObjectName("@MaDeByPhYsIcS@");
                        Qt3D::QMatrixTransform* matrix= new Qt3D::QMatrixTransform(m,physics_transform);
                        physics_transform->addTransform(matrix);
                        e->addComponent(physics_transform);
                        m_attached_matrix=matrix;
                    }
                }
            }
    }*/
        if(e->propertyName() == QByteArrayLiteral("updateTransform")){
            QMatrix4x4 mat= e->value().value<QMatrix4x4>();
            m_outputTransform_matrix->setMatrix(mat);
            emit outputTransformChanged();
        }
        if(e->propertyName() == QByteArrayLiteral("notifyCollision")){
            PhysicsCollisionEventPtrList collitions_list=e->value().value<PhysicsCollisionEventPtrList>();
            if(collitions_list.size()==0){
                if(m_hasCollided){
                    m_hasCollided=false;
                    emit hasCollidedChanged(m_hasCollided);
                }
                m_collitionsList.clear();
                emit collitionsListChanged();
            }
            else{
                m_collitionsList.clear();
                Q_FOREACH(PhysicsCollisionEventPtr event_ptr,collitions_list){
                    m_collitionsList.append(event_ptr);
                    if(m_collitionsList.last()->isNew()){
                        emit collided(m_collitionsList.last().data());
                    }
                }
                if(!m_hasCollided){
                    m_hasCollided=true;
                    emit hasCollidedChanged(m_hasCollided);
                }
                emit collitionsListChanged();
            }
        }
    }
}






}



