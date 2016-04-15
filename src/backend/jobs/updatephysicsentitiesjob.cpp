#include <backend/jobs/updatephysicsentitiesjob.h>
#include <backend/backendtypes/physicsentity.h>
#include <backend/backendtypes/physicsgeometryrenderer.h>
#include <backend/backendtypes/physicsbodyinfobackendnode.h>
#include <backend/backendtypes/physicsworldinfobackendnode.h>
#include <backend/backendtypes/physicstransform.h>
#include <backend/backendtypes/physicsgeometry.h>
#include <backend/backendtypes/physicsattribute.h>
#include <backend/backendtypes/physicsbuffer.h>

#include <backend/physicsmanager.h>
namespace Physics {


UpdatePhysicsEntitiesJob::UpdatePhysicsEntitiesJob(PhysicsManager* manager):
    Qt3DCore::QAspectJob()
{
    m_manager=manager;
}

void UpdatePhysicsEntitiesJob::run(){
    m_visit_queue.clear();
    if(!m_manager->rootEntityId().isNull()){
        /*Remove  not enabled subtrees*/
        removeNotEnabledSubtrees(m_manager->rootEntityId());
        /*Start update*/
        Visit_Data tmp_visit_data;
        tmp_visit_data.set(m_manager->rootEntityId(),QMatrix4x4(),false);
        m_visit_queue.enqueue(tmp_visit_data);
        while(!m_visit_queue.isEmpty()){
            tmp_visit_data=m_visit_queue.dequeue();
            iterative_step(tmp_visit_data.node_id, tmp_visit_data.parent_matrix,tmp_visit_data.forceUpdateMS);
        }
    }
}

void UpdatePhysicsEntitiesJob::removeNotEnabledSubtrees(Qt3DCore::QNodeId rootId){
    QQueue<Qt3DCore::QNodeId> nodesToVisit, nodesToRemove;
    nodesToVisit.enqueue(rootId);
    PhysicsEntity* entity;
    Qt3DCore::QNodeId current_node;
    while(!nodesToVisit.empty()){
        current_node=nodesToVisit.dequeue();
        if(!m_manager->m_resources.contains(current_node)) continue;
        entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](current_node));
        if(!entity) continue;
        if(!entity->isEnabled())//you need this info, even if the node is not dirty
            nodesToRemove.enqueue(current_node);
        else if(!entity->parentId().isNull() && nodesToRemove.contains(entity->parentId()))
            nodesToRemove.enqueue(current_node);
        for(Qt3DCore::QNodeId childId : entity->childrenIds())
            nodesToVisit.enqueue(childId);
    }
    while(!nodesToRemove.empty()){
        current_node=nodesToRemove.dequeue();
        if(m_manager->m_Id2RigidBodies.contains(current_node)){
            PhysicsAbstractRigidBody* body =m_manager->m_Id2RigidBodies[current_node];
            m_manager->m_Id2RigidBodies.remove(current_node);
            m_manager->m_RigidBodies2Id.remove(body);
            m_manager->m_physics_world->removeRigidBody(body);
            delete body;
        }
    }

}

void UpdatePhysicsEntitiesJob::iterative_step(Qt3DCore::QNodeId node_id, QMatrix4x4 parent_matrix, bool forceUpdateMS)
{
    if(node_id.isNull()) return;
    if(!m_manager->m_resources.contains(node_id)) return;
    PhysicsEntity* entity= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](node_id));
    if(!entity || !entity->isEnabled() ) return;
    QMatrix4x4 current_global_matrix=parent_matrix;
    if(isDefiningBody(entity)){
        bool isBodyNew=false;
        PhysicsAbstractRigidBody* rigid_body;
        PhysicsGeometryRenderer* entity_geometry_renderer=static_cast<PhysicsGeometryRenderer*>(m_manager->m_resources.operator [](entity->geometry_renderer()));
        if(m_manager->m_Id2RigidBodies.contains(entity->peerUuid()))
            rigid_body=m_manager->m_Id2RigidBodies[entity->peerUuid()];
        else{
            rigid_body=createRigidBodyFromMesh(entity_geometry_renderer);
            rigid_body->setCollisionMargin(rigid_body->collisionMargin()*m_manager->m_physics_world->scaleFactor());
            isBodyNew=true;
        }
        /*Update collision Shape*/
        if(isRequiringShapeUpdate(entity_geometry_renderer)){
            /*Destroy the rigid body and make a new one*/
            m_manager->m_Id2RigidBodies.remove(node_id);
            m_manager->m_RigidBodies2Id.remove(rigid_body);
            m_manager->m_physics_world->removeRigidBody(rigid_body);
            delete rigid_body;
            rigid_body=createRigidBodyFromMesh(entity_geometry_renderer);
            rigid_body->setCollisionMargin(rigid_body->collisionMargin()*m_manager->m_physics_world->scaleFactor());
            isBodyNew=true;
        }
        /*Update Body properties*/
        bool bodyNeedsReadd=isBodyNew;
        PhysicsBodyInfoBackendNode* entity_body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::MaskChanged)){
            rigid_body->setMask(entity_body_info->mask());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::MaskChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::GroupChanged)){
            rigid_body->setGroup(entity_body_info->group());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::GroupChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::MassChanged)){
            rigid_body->setMass(entity_body_info->mass());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::MassChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::KinematicChanged)){
            rigid_body->setKinematic(entity_body_info->kinematic());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::KinematicChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::FallInertiaChanged)){
            rigid_body->setFallInertia(entity_body_info->fallInertia());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::FallInertiaChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::RestistutionChanged)){
            rigid_body->setRestitution(entity_body_info->restitution());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::RestistutionChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::FrictionChanged)){
            rigid_body->setFriction(entity_body_info->friction());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::FrictionChanged;
            bodyNeedsReadd=true;
        }
        if(isBodyNew || entity_body_info->dirtyFlags().testFlag(PhysicsBodyInfoBackendNode::DirtyFlag::RollingFrictionChanged)){
            rigid_body->setRollingFriction(entity_body_info->rollingFriction());
            entity_body_info->dirtyFlags() &= ~PhysicsBodyInfoBackendNode::DirtyFlag::RollingFrictionChanged;
            bodyNeedsReadd=true;
        }
        if(bodyNeedsReadd){
            if(m_manager->m_Id2RigidBodies.contains(node_id)){
                m_manager->m_physics_world->removeRigidBody(rigid_body);
                m_manager->m_physics_world->addRigidBody(rigid_body);

            }
            else{
                //New body
                m_manager->m_Id2RigidBodies[node_id]=rigid_body;
                m_manager->m_RigidBodies2Id[rigid_body]=node_id;
                m_manager->m_physics_world->addRigidBody(rigid_body);
            }

        }
        /*Update Motion State*/
        PhysicsTransform* inputTransform=Q_NULLPTR;
        if(!entity_body_info->inputTransform().isNull() && m_manager->m_resources.contains(entity_body_info->inputTransform())){
            inputTransform=static_cast<PhysicsTransform*>(m_manager->m_resources.operator [](entity_body_info->inputTransform()));
        }
        /*The input transform has changed; the new position is taken from that.*/
        if(inputTransform!=Q_NULLPTR && (inputTransform->isDirty() || isBodyNew )){
            current_global_matrix=current_global_matrix*inputTransform->transformMatrix();
            forceUpdateMS=true;
            inputTransform->setDirty(false);
        }
        /*Otherwise use the matrix from the simulation*/
        else{
            current_global_matrix=current_global_matrix*entity_body_info->localTransform();
        }
        if(forceUpdateMS){
            rigid_body->setWorldTransformation(current_global_matrix,m_manager->m_physics_world->scaleFactor());
        }
    }
    else {
        /*If the node doesn't define a valid body then remove a former associated body*/
        if(m_manager->m_Id2RigidBodies.contains(node_id)){
            PhysicsAbstractRigidBody* rigid_body= m_manager->m_Id2RigidBodies.operator [](node_id);
            m_manager->m_Id2RigidBodies.remove(node_id);
            m_manager->m_RigidBodies2Id.remove(rigid_body);
            m_manager->m_physics_world->removeRigidBody(rigid_body);
            delete rigid_body;
        }
        if(!entity->transform().isNull() && m_manager->m_resources.contains(entity->transform())){
            /*Entity with only a transformation*/
            PhysicsTransform* entity_transform=static_cast<PhysicsTransform*>(m_manager->m_resources.operator [](entity->transform()));
            current_global_matrix=current_global_matrix*entity_transform->transformMatrix();
            if(entity_transform->isDirty()){
                forceUpdateMS=true;
                entity_transform->setDirty(false);
            }
        }
    }

    /*Update Physic World settings*/
    if(!entity->physicsWorldInfo().isNull() && m_manager->m_resources.contains(entity->physicsWorldInfo())){
        PhysicsWorldInfoBackendNode* entity_physics_world_info=static_cast<PhysicsWorldInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsWorldInfo()));
        if(entity_physics_world_info->dirtyFlags().testFlag(PhysicsWorldInfoBackendNode::DirtyFlag::GravityChanged)){
            m_manager->m_physics_world->setGravity(entity_physics_world_info->gravity()*m_manager->m_physics_world->scaleFactor());
            entity_physics_world_info->dirtyFlags() &= ~PhysicsWorldInfoBackendNode::DirtyFlag::GravityChanged;
            m_manager->m_physics_world->setDebug(entity_physics_world_info->debug());
        }
        if(entity_physics_world_info->dirtyFlags().testFlag(PhysicsWorldInfoBackendNode::DirtyFlag::ScaleFactorChanged)){
            //This requires that all the objects are removed
            m_manager->m_physics_world->setScaleFactor(entity_physics_world_info->scaleFactor());
            m_manager->m_physics_world->setGravity(entity_physics_world_info->gravity()*m_manager->m_physics_world->scaleFactor());
            m_manager->m_Id2RigidBodies.clear();
            m_manager->m_RigidBodies2Id.clear();
            entity_physics_world_info->dirtyFlags() &= ~PhysicsWorldInfoBackendNode::DirtyFlag::ScaleFactorChanged;
            return;
        }
    }
    /*Next call*/
    Visit_Data child_data;
    for(Qt3DCore::QNodeId childId : entity->childrenIds()){
        child_data.set(childId, current_global_matrix,forceUpdateMS);
        m_visit_queue.enqueue(child_data);
    }
}
bool UpdatePhysicsEntitiesJob::isRequiringShapeUpdate(PhysicsGeometryRenderer* entity_geometry_renderer){
    if(entity_geometry_renderer->isDirty()) return true;
    Qt3DCore::QNodeId geometryId;
    if(!entity_geometry_renderer->m_geometry.isNull()){
        geometryId=entity_geometry_renderer->m_geometry;
    }
    else{
        geometryId=entity_geometry_renderer->m_geometry_functor.data()->operator ()()->id();
    }
    PhysicsGeometry* geometry=static_cast<PhysicsGeometry*>(m_manager->m_resources.operator [](geometryId));
    Q_FOREACH(Qt3DCore::QNodeId attrId,geometry->attributes()){
        if(!m_manager->m_resources.contains(attrId)) continue;
        PhysicsAttribute* attribute=static_cast<PhysicsAttribute*>(m_manager->m_resources.operator [](attrId));
        if(attribute->objectName()==Qt3DRender::QAttribute::defaultPositionAttributeName()){
            if(attribute->isDirty()) return true;
            PhysicsBuffer* buffer_node=static_cast<PhysicsBuffer*>(m_manager->m_resources.operator [](attribute->bufferId()));
            if(buffer_node->isDirty()) return true;
        }
        else if(attribute->attributeType()==Qt3DRender::QAttribute::IndexAttribute){
            if(attribute->isDirty()) return true;
            if(m_manager->m_resources.contains(attribute->bufferId())){
                PhysicsBuffer* buffer_node=static_cast<PhysicsBuffer*>(m_manager->m_resources.operator [](attribute->bufferId()));
                if(buffer_node->isDirty()) return true;
            }
        }
    }
    return false;
}
bool UpdatePhysicsEntitiesJob::isDefiningBody(PhysicsEntity* entity){
    /*A body must have a body info which should be enabled*/
    if(!entity->physicsBodyInfo().isNull() && m_manager->m_resources.contains(entity->physicsBodyInfo())){
        PhysicsBodyInfoBackendNode* entity_body_info=static_cast<PhysicsBodyInfoBackendNode*>(m_manager->m_resources.operator [](entity->physicsBodyInfo()));
        if(!entity_body_info->isEnabled()) return false;
    }else return false;

    /*A body must have a geometry suitable for defining a collition shape*/
    if(entity->geometry_renderer().isNull() || !m_manager->m_resources.contains(entity->geometry_renderer())) return false;
    PhysicsGeometryRenderer* entity_geometry_renderer=static_cast<PhysicsGeometryRenderer*>(m_manager->m_resources.operator [](entity->geometry_renderer()));
    if(!entity_geometry_renderer->isEnabled()) return false;
    if(entity_geometry_renderer->m_primitiveType!=Qt3DRender::QGeometryRenderer::Triangles) return false;
    //if(entity_geometry_renderer->m_primitiveCount<=0) return false;
    if(entity_geometry_renderer->m_geometry.isNull() && entity_geometry_renderer->m_geometry_functor.isNull())
        return false;
    Qt3DCore::QNodeId geometryId;
    if(!entity_geometry_renderer->m_geometry.isNull()){
        geometryId=entity_geometry_renderer->m_geometry;
    }
    else{
        geometryId=entity_geometry_renderer->m_geometry_functor.data()->operator ()()->id();
    }
    if(geometryId.isNull() || !m_manager->m_resources.contains(geometryId)) return false;
    PhysicsGeometry* geometry=static_cast<PhysicsGeometry*>(m_manager->m_resources.operator [](geometryId));
    if(!geometry->isEnabled()) return false;
    if(geometry->attributes().isEmpty()) return false;
    PhysicsAttribute* vertexPositionAttribute=Q_NULLPTR;
    Q_FOREACH(Qt3DCore::QNodeId attrId,geometry->attributes()){
        if(attrId.isNull() || !m_manager->m_resources.contains(attrId)) continue;
        vertexPositionAttribute=static_cast<PhysicsAttribute*>(m_manager->m_resources.operator [](attrId));
        if(!vertexPositionAttribute) continue;
        if(vertexPositionAttribute->objectName()==Qt3DRender::QAttribute::defaultPositionAttributeName()){
            break;
        }
        else
            vertexPositionAttribute=Q_NULLPTR;
    }
    if(!vertexPositionAttribute) return false;
    if(vertexPositionAttribute->count()==0) return false;
    if(vertexPositionAttribute->bufferId().isNull() || !m_manager->m_resources.contains(vertexPositionAttribute->bufferId())) return false;
    PhysicsBuffer* buffer_node=static_cast<PhysicsBuffer*>(m_manager->m_resources.operator [](vertexPositionAttribute->bufferId()));
    if(!buffer_node) return false;
    if(!buffer_node->isEnabled()) return false;
    return true;
}

PhysicsAbstractRigidBody* UpdatePhysicsEntitiesJob::createRigidBodyFromMesh(PhysicsGeometryRenderer* entity_geometry_renderer){
    QVariantMap geometric_info;
    entity_geometry_renderer->setDirty(false);
    geometric_info["Type"]="Generic";
    Qt3DCore::QNodeId geometryId;
    if(!entity_geometry_renderer->m_geometry.isNull()){
        geometryId=entity_geometry_renderer->m_geometry;
    }
    else{
        geometryId=entity_geometry_renderer->m_geometry_functor.data()->operator ()()->id();
    }
    PhysicsGeometry* geometry=static_cast<PhysicsGeometry*>(m_manager->m_resources.operator [](geometryId));
    QVector<QVector3D> vertexPosition;
    QSet<quint16> index_Set;
    Q_FOREACH(Qt3DCore::QNodeId attrId,geometry->attributes()){
        PhysicsAttribute* attribute=static_cast<PhysicsAttribute*>(m_manager->m_resources.operator [](attrId));
        if(!attribute) continue;
        if(attribute->objectName()==Qt3DRender::QAttribute::defaultPositionAttributeName()){
            vertexPosition=attribute->asVector3D();
            attribute->setDirty(false);
            PhysicsBuffer* buffer_node=static_cast<PhysicsBuffer*>(m_manager->m_resources.operator [](attribute->bufferId()));
            buffer_node->setDirty(false);
        }
        else if(attribute->attributeType()==Qt3DRender::QAttribute::IndexAttribute){
            if(!attribute->bufferId().isNull() && m_manager->m_resources.contains(attribute->bufferId())){
                attribute->setDirty(false);
                QByteArray buffer;
                if(!m_manager->m_resources.contains(attribute->bufferId())) continue;
                PhysicsBuffer* buffer_node=static_cast<PhysicsBuffer*>(m_manager->m_resources.operator [](attribute->bufferId()));
                buffer_node->setDirty(false);
                if(buffer_node->bufferFunctor().isNull()){
                    buffer=buffer_node->data();
                }
                else{
                    buffer=buffer_node->bufferFunctor().data()->operator ()();
                }
                const char *rawBuffer = buffer.constData();
                rawBuffer += attribute->byteOffset();
                const quint16* fptr;
                int stride;
                switch (attribute->dataType()) {
                case Qt3DRender::QAttribute::UnsignedShort:
                    stride = sizeof(quint16) * attribute->dataSize();
                    break;
                default:
                    qDebug()<< "can't convert";
                }
                if (attribute->byteStride() != 0)
                    stride = attribute->byteStride();
                index_Set.reserve(attribute->count());
                for (uint c = 0; c < attribute->count(); ++c) {
                    fptr = reinterpret_cast<const quint16*>(rawBuffer);
                    for (uint i = 0, m = qMin(attribute->dataSize(), 3U); i < m; ++i)
                        index_Set.insert(fptr[i]);
                    rawBuffer += stride;
                }
            }
        }
    }
    QVector<QVector3D> v=vertexPosition;
    vertexPosition.clear();
    vertexPosition.reserve(index_Set.size());
    Q_FOREACH(quint16 index,index_Set.values()){
        if(index<v.size())
            vertexPosition.append(v[index]*m_manager->m_physics_world->scaleFactor());
    }
    geometric_info["Points"]=QVariant::fromValue(vertexPosition);
    return m_manager->m_physics_factory->create_rigid_body(geometric_info);
}


}
