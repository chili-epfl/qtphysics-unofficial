#include "qt3dbody.h"

QMatrix4x4 getWorldTranformationMatrix(Qt3D::QEntity* entity){
    if(!entity) return  QMatrix4x4();
    Qt3D::QTransform* entity_transform=NULL;
    for(Qt3D::QComponent* component: entity->components()){
        if(component->isEnabled()){
            if(component->inherits("Qt3D::QTransform")){
                entity_transform=qobject_cast<Qt3D::QTransform*>(component);
            }
        }
    }
    if(entity_transform!=NULL){
        return getTranformationMatrix(entity->parentEntity())*entity_transform->matrix();
    }
    else return getTranformationMatrix(entity->parentEntity());
}


/*Check if entity parent is a mesh with a transform.
  Not sure this is the best way to check dependency*/
bool isDependent(Qt3D::QEntity *entity){
    if(!entity->parent()) return false;
    bool hasMesh=false, hasTransform=false;
    for(Qt3D::QComponent* c: entity->parent()->components()){
        if(c->inherits("Qt3D::QAbstractMesh"))
            hasMesh=true;
        else if(c->inherits("Qt3D::QTransform"))
            hasTransform=true;
    }
        return (hasMesh && hasTransform);

}

Bullet::QT3DBody::QT3DBody(QQuickItem* parent):
    AbstractBody(parent),
    m_entity(0),
    m_sceneRoot(0),
    m_isWorldTransformationFromProperty(false)
{
    init();
}

void Bullet::QT3DBody::init(){
    m_shape=new btEmptyShape();

    btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
    if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
        m_shape->calculateLocalInertia(m_mass,inertia);

    m_motionState = new MotionState(m_transformation,QMatrix4x4());

    if(!m_kinematic)
        connect(m_motionState,SIGNAL(motionStateChanged(QMatrix4x4)),this,SIGNAL(worldTransformationChanged(QMatrix4x4)));

    m_rigidBodyCI=new btRigidBody::btRigidBodyConstructionInfo(m_mass,m_motionState, m_shape,inertia);
    m_rigidBody= new btRigidBody(*m_rigidBodyCI);

    m_rigidBody->setRestitution(m_restitution);

    m_rigidBody->setFriction(m_friction);

    m_rigidBody->setRollingFriction(m_rollingFriction);

    if(m_world)
        m_world->addRigidBody(m_rigidBody,m_group,m_mask);
}

void Bullet::QT3DBody::clear(){
    if(m_world)
        m_world->removeRigidBody(m_rigidBody);
    delete m_rigidBody;
    delete m_rigidBodyCI;
    delete m_motionState;
    delete m_shape;

}

void Bullet::QT3DBody::setEntity(Qt3D::QEntity *entity, bool force){
    if(m_entity!=entity || force){
        if(!m_sceneRoot) return;

        if(isDependent(entity)){
            qWarning()<<"Dependent entity. Entities should be root. Force detachment by setting ForceDetach flag";
        }

        m_entity=entity;

        QList<Qt3D::QEntity*> l=m_entity->children<Qt3D::QEntity*>();

        if(m_world)
            m_world->lock();

        if(m_shape)
           delete m_shape;

        /* The entity either doesn't have any children ot the flag
         * or the flag INCLUDECHILDER is not set. As results the shape will be made from the
         * the mesh of entity*/
        if( l.size()==0 || !m_options.testFlag(INCLUDECHILDREN)){
            m_shape=generateSingleBody(m_entity);
        }/*Otherwise a compund shape is created.*/
        else{
            m_shape=generateCompoundBody(m_entity);
        }

        /*Warning center*/
        btVector3 inertia(m_fallInertia.x(),m_fallInertia.y(),m_fallInertia.z());
        if(m_fallInertia.x()==0 && m_fallInertia.y()==0 && m_fallInertia.z()==0)
            m_shape->calculateLocalInertia(m_mass,inertia);
        m_rigidBody->setCollisionShape(m_shape);
        m_rigidBody->setMassProps(m_mass,inertia);

        if(m_world)
            m_world->unlock();

        /*If the input matrix is not provided, set the motion state from the entity QTransform*/
        if(!m_isWorldTransformationFromProperty){
           setWorldTransformation(getWorldTranformationMatrix(m_entity),false);
        }
    }
}

void Bullet::QT3DBody::setSceneRoot(Qt3D::QEntity *sceneRoot){
    if(m_sceneRoot!=sceneRoot){
        m_sceneRoot=sceneRoot;
        setEntity(m_entity,true);
        emit sceneRootChanged();
    }
}

void Bullet::QT3DBody::setKinematic(bool kinematic,bool force){
    if(m_kinematic!=kinematic || force){
        m_kinematic=kinematic;
        if(!m_entity) return;
        if(m_kinematic){
            if(m_isWorldTransformationFromProperty){
                connect(this,SIGNAL(worldTransformationChanged(QMatrix4x4)),this,SLOT(updateMotionState()));
            }
        }
        else{
            if(m_isWorldTransformationFromProperty){
                disconnect(this,SIGNAL(inputTransformChanged()),this,SLOT(updateMotionState()));
            }
            connect(this,SIGNAL(worldTransformationChanged(QMatrix4x4))
        }
    }
}

void Bullet::QT3DBody::updateMotionState(){
    if(m_inputTransformIsDefined){
        m_motionState->setWorldTransform(m_inputTransform);
    }
}

void Bullet::QT3DBody::setWorldTransformation(QMatrix4x4 m,bool isFromProperty ){
    if(m_worldTransformation!=m){
        m_worldTransformation=m;
        m_isWorldTransformationFromProperty=isFromProperty;
        setKinematic(m_kinematic,true);
    }
}



void Bullet::QT3DBody::updateBehaviour(){
    if(m_options.testFlag(KINEMATIC)){
        addtokinematicpool;
    }
    else if(m_options.testFlag(DIRECTTRANSFORM) && !m_isDependent){
        setDirectTransform();
    }
    else if(m_options.testFlag(DIRECTTRANSFORM) && m_isDependent && m_options.testFlag(FORCEDEPENDENTUPDATE)){

    }
    else if(m_options.testFlag(DIRECTTRANSFORM) && m_isDependent && !m_options.testFlag(FORCEDEPENDENTUPDATE)){
        qWarning()<<"Direct Transform not possible for dependent object without FORCEDEPENDENTUPDATE";
    }
}


void Bullet::QT3DBody::updateMotionState(){

}

void Bullet::QT3DBody::setDirectTrasform(bool enable){
    if(enable){
        if(m_DT_transform==0){
            m_DT_transform=new Qt3D::QTransform(this);
            m_DT_transform->setObjectName("DIRECTTRANSFORM@BULLET");
            m_DT_matrix=new Qt3D::QMatrixTransform(m_transformation,m_DT_transform);
            m_DT_transform->addTransform(m_DT_matrix);
            m_entity->addComponent(m_DT_transform);
        }
        for(Qt3D::QComponent* component: m_entity->components()){
            if(component->isEnabled()){
                if(component->inherits("Qt3D::QTransform") && component->objectName().compare("DIRECTTRANSFORM@BULLET")!=0){
                    component->setEnabled(false);
                    break;
                }
            }
        }
    }
    else{
        for(Qt3D::QComponent* component: m_entity->components()){
            if(component->isEnabled()){
                if(component->inherits("Qt3D::QTransform") && component->objectName().compare("DIRECTTRANSFORM@BULLET")!=0){
                    component->setEnabled(true);
                    break;
                }
            }
        }
        m_DT_transform->setEnabled(false);
    }
}


btCollisionShape* Bullet::QT3DBody::generateSingleShape(Qt3D::QEntity *entity){
    Bullet::AbstractBody* shape=0;
    for(Qt3D::QComponent* c : entity->components()){
        if(c->isEnabled()){
            if(c-> inherits("Qt3D::QAbstractMesh")){
                if(c->inherits("Qt3D::QSphereMesh")){
                    Qt3D::QSphereMesh* mesh=qobject_cast<Qt3D::QSphereMesh*>(c);
                    shape=new btSphereShape(mesh->radius());
                }
                else if (c->inherits("Qt3D::QCuboidMesh")){
                    Qt3D::QCuboidMesh* mesh=qobject_cast<Qt3D::QCuboidMesh*>(c);
                    shape=new btBoxShape(btVector3(mesh->xExtent()/2,mesh->yExtent()/2,mesh->zExtent()/2));
                }
                else{
                    Qt3D::QAbstractMesh* mesh=qobject_cast<Qt3D::QAbstractMesh*>(c);
                    Qt3D::QAbstractMeshFunctorPtr mesh_functor=mesh->meshFunctor();
                    Qt3D::QMeshDataPtr data_ptr=mesh_functor.data()->operator ()();
                    Qt3D::QMeshData* mesh_data=data_ptr.data();
                    QVector<QVector3D> vertexPositions=mesh_data->attributeByName("vertexPosition")->asVector3D();
                    btScalar* points=new btScalar[vertexPositions.size()*3];
                    for(int i=0;i<vertexPositions.size();i++){
                        points[3*i]=vertexPositions[i].x();
                        points[3*i+1]=vertexPositions[i].y();
                        points[3*i+2]=vertexPositions[i].z();
                    }
                    shape=new btConvexHullShape(points,vertexPositions.size());
                    delete points;
                }
            }

        }
    }
    return shape;
}


void Bullet::QT3DBody::generateCompoundShape_recursive_step(Qt3D::QEntity *entity,QMatrix4x4 parentTransform,btCompoundShape* compoundShape){
    btCollisionShape* shape=generateSingleShape(entity);
    if(!shape) return;
    Qt3D::QTransform* entity_transform=0;
    for(Qt3D::QComponent* component: entity->components()){
        if(component->isEnabled()){
            if(component->inherits("Qt3D::QTransform")){
                entity_transform=qobject_cast<Qt3D::QTransform*>(component);
                break;
            }
        }
    }
    QMatrix4x4 localTransform(parentTransform);

    if(entity_transform)
        localTransform*=entity_transform->matrix();

    btMatrix3x3 rotation(localTransform.operator ()(0,0),localTransform.operator ()(1,0),localTransform.operator ()(2,0),
                           localTransform.operator ()(0,1),localTransform.operator ()(1,1),localTransform.operator ()(2,1),
                           localTransform.operator ()(0,2),localTransform.operator ()(1,2),localTransform.operator ()(2,2));
    btVector3 translation(localTransform.operator ()(0,3),localTransform.operator ()(1,3),localTransform.operator ()(2,3));

    compoundShape->addChildShape(btTransform(rotation,translation),shape);

    QList<Qt3D::QEntity*> children=entity->findChildren<Qt3D::QEntity*>(QString(),Qt::FindDirectChildrenOnly);

    for(Qt3D::QEntity* e :children){
        generateCompoundShape_recursive_step(e,localTransform,compoundShape);
    }
}

btCollisionShape* Bullet::QT3DBody::generateCompoundShape(Qt3D::QEntity *entity){
    btCollisionShape* rootShape=generateSingleShape(entity);
    if(!rootShape){
        qWarning()<<"QT3DBody::generateCompoundShape got an entity with an invalid root mesh";
        return new btEmptyShape();
    }
    btCompoundShape* shape=new btCompoundShape();
    shape->addChildShape(btTransform::getIdentity(),rootShape);
    QList<Qt3D::QEntity*> children=entity->findChildren<Qt3D::QEntity*>(QString(),Qt::FindDirectChildrenOnly);
    for(Qt3D::QEntity* e :children){
        generateCompoundShape_recursive_step(e,QMatrix4x4(),shape);
    }
}

void Bullet::QT3DBody::setInputTrasformation(QMatrix4x4 m, bool fromUser){

}
