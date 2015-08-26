#include "updatephysicsentitiesjob.h"
#include "backendtypes/physicsentity.h"
#include "backendtypes/physicsmesh.h"
#include "backendtypes/physicsbodyinfobackendnode.h"
#include "backendtypes/physicsworldinfobackendnode.h"
#include "backendtypes/physicstransform.h"

#include "physicsmanager.h"
namespace Physics {


UpdatePhysicsEntitiesJob::UpdatePhysicsEntitiesJob(PhysicsManager* manager):
    Qt3D::QAspectJob()
{
    m_manager=manager;
}

void UpdatePhysicsEntitiesJob::run(){
    recursive_step(m_manager->rootEntityId(),QMatrix4x4());
}

void UpdatePhysicsEntitiesJob::recursive_step(Qt3D::QNodeId node_id, QMatrix4x4 parent_matrix){
    if(node_id.isNull()) return;
    PhysicsEntity* entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](node_id));

    QMatrix4x4 current_global_matrix=parent_matrix;

    /*The objects belonging to the physic world are:
     * 1) Object with an abstract mesh and a transformation but without a bodyinfo -> those are static
     * 2) Object with an abstract mesh, a transformation and a bodyinfo
     * 3) Object with a transformation and a bodyinfo -> those are not rendered
     * */
    if(!entity->default_transform().isNull() &&
            (!entity->abstractmesh().isNull() ||
            (!entity->physicsBodyInfo().isNull()))){

        PhysicsTransform* entity_default_transform=static_cast<PhysicsTransform*>(m_manager->m_resources.operator [](entity->default_transform()));

        PhysicsTransform* entity_physics_transform=Q_NULLPTR;
        PhysicsMesh* entity_mesh=Q_NULLPTR;
        PhysicsBodyInfoBackendNode* entity_body_info=Q_NULLPTR;

        if(!entity->abstractmesh().isNull())
            entity_mesh=static_cast<PhysicsMesh*>(m_manager->m_resources.operator [](entity->abstractmesh()));

        if(!entity->physics_transform().isNull())
            entity_physics_transform=static_cast<PhysicsTransform*>(m_manager->m_resources.operator [](entity->physics_transform()));

        if(!entity->physicsBodyInfo().isNull())
            entity_body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));

        PhysicsAbstractRigidBody* rigid_body;

        /*The body needs to be created*/
        if(!m_manager->m_rigid_bodies.contains(node_id)){
            QVariantMap geometric_info;
            /*If the shape details are defined , the collition shape is not derived by the mesh nature*/
            if(entity_body_info!=Q_NULLPTR && entity_body_info->shapeDetails().size()>0){
                QVariantMap shapeDetails=entity_body_info->shapeDetails();
                QString type=shapeDetails["Type"].toString();
                if(type=="Cuboid"){
                    geometric_info["Type"]="Cuboid";
                    geometric_info["X_Dim"]=shapeDetails["X_Dim"];
                    geometric_info["Y_Dim"]=shapeDetails["Y_Dim"];
                    geometric_info["Z_Dim"]=shapeDetails["Z_Dim"];
                }
                else if(type=="Sphere"){
                    geometric_info["Type"]="Sphere";
                    geometric_info["Radius"]=shapeDetails["Radius"];
                }
                else if(type=="StaticPlane"){
                    geometric_info["Type"]="StaticPlane";
                    geometric_info["PlaneNormal"]=shapeDetails["PlaneNormal"];
                    geometric_info["PlaneConstant"]=shapeDetails["PlaneConstant"];
                }
                else{
                    qFatal("Unknown shape type");
                }
            }
            /*Otherwise the geomtric info are extracted by the mesh*/
            else{
                if(entity_mesh->m_type==PhysicsMesh::Mesh_Type::CUBOID){
                    geometric_info["Type"]="Cuboid";
                    geometric_info["X_Dim"]=entity_mesh->m_x_dim;
                    geometric_info["Y_Dim"]=entity_mesh->m_y_dim;
                    geometric_info["Z_Dim"]=entity_mesh->m_z_dim;

                }
                if(entity_mesh->m_type==PhysicsMesh::Mesh_Type::SPHERE){
                    geometric_info["Type"]="Sphere";
                    geometric_info["Radius"]=entity_mesh->m_radius;
                }
                else{
                    geometric_info["Type"]="Generic";
                    Qt3D::QMeshDataPtr data_ptr=entity_mesh->m_meshfunctor.data()->operator ()();
                    Qt3D::QMeshData* mesh_data=data_ptr.data();
                    QVector<QVector3D> vertexPosition=mesh_data->attributeByName("vertexPosition")->asVector3D();
                    geometric_info["Points"]=QVariant::fromValue(vertexPosition.toList());
                }
            }
            rigid_body=m_manager->m_physics_factory->create_rigid_body(geometric_info);
            m_manager->m_physics_world->addBody(rigid_body);
        }
        /*The body was already created*/
        else{
            rigid_body=m_manager->m_rigid_bodies[node_id];
        }

        /*Update body properties*/
        if(entity_default_transform->isDirty() || entity_body_info==Q_NULLPTR || entity_physics_transform==Q_NULLPTR ){
            /*Kinematic object: the motion state is updated according to the new position*/
            current_global_matrix=current_global_matrix*entity_default_transform->transformMatrix();
            rigid_body->setWorldTransformation(current_global_matrix);
        }
        else{
            current_global_matrix=current_global_matrix*entity_physics_transform->transformMatrix();
        }
        if(entity_mesh!=Q_NULLPTR && entity_mesh->isDirty()){
            //TODO
        }
        if(entity_body_info!=Q_NULLPTR){
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::MaskChanged)){
                 rigid_body->setMask(entity_body_info->mask());
                entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::MaskChanged;
            }
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::GroupChanged)){
                    rigid_body->setGroup(entity_body_info->group());
                    entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::GroupChanged;
            }
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::MassChanged)){
                    rigid_body->setMass(entity_body_info->mass());
                    entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::MassChanged;
            }
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::FallInertiaChanged)){
                    rigid_body->setFallInertia(entity_body_info->fallInertia());
                    entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::FallInertiaChanged;
            }
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::RestistutionChanged)){
                    rigid_body->setRestitution(entity_body_info->restitution());
                    entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::RestistutionChanged;
            }
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::FrictionChanged)){
                    rigid_body->setFriction(entity_body_info->friction());
                    entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::FrictionChanged;
            }
            if(entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::RollingFrictionChanged)){
                    rigid_body->setRollingFriction(entity_body_info->rollingFriction());
                    entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::RollingFrictionChanged;
            }
        }
        m_manager->m_rigid_bodies[node_id]=rigid_body;
    }

    /*Entity containing a world component*/
    if(!entity->physicsWorldInfo().isNull()){
        PhysicsWorldInfoBackendNode* entity_physics_world_info=static_cast<PhysicsWorldInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsWorldInfo()));
        if(entity_physics_world_info->dirtyFlags().testFlag(PhysicsWorldInfoBackendNode::DirtyFlag::GravityChanged)){
            m_manager->m_physics_world->setGravity(entity_physics_world_info->gravity());
            entity_physics_world_info->dirtyFlags() &= ~PhysicsWorldInfoBackendNode::DirtyFlag::GravityChanged;
        }
    }
    /*Next call*/
    for(Qt3D::QNodeId childId : entity->childrenIds())
        recursive_step(childId, current_global_matrix);
}







}
