#include "physicsmesh.h"

#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsMesh::PhysicsMesh():
    Qt3D::QBackendNode(),
    m_objectName(),
    m_dirty(false),
    m_enabled(false),
    m_meshfunctor()
{
    m_manager=Q_NULLPTR;
    m_type=GENERAL;
}

void PhysicsMesh::setManager(PhysicsManager *manager){
        m_manager=manager;
}


PhysicsMesh::~PhysicsMesh(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsMesh::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QAbstractMesh *mesh = static_cast<Qt3D::QAbstractMesh*>(peer);   
    if(mesh->inherits("Qt3D::QCuboidMesh")){
        m_type=CUBOID;
        Qt3D::QCuboidMesh* _mesh =static_cast<Qt3D::QCuboidMesh*>(peer);
        m_x_dim=_mesh->xExtent();
        m_y_dim=_mesh->yExtent();
        m_z_dim=_mesh->zExtent();
    }
    else if (mesh->inherits("Qt3D::QSphereMesh")){
        m_type=SPHERE;
        Qt3D::QSphereMesh* _mesh =static_cast<Qt3D::QSphereMesh*>(peer);
        m_radius=_mesh->radius();
    }
    else {
        m_type=GENERAL;
    }
    m_objectName = peer->objectName();
    m_dirty=true;
    m_enabled=mesh->isEnabled();
    setMeshFunctor(mesh->meshFunctor());
}

void PhysicsMesh::setMeshFunctor(Qt3D::QAbstractMeshFunctorPtr functor)
{
    if (m_meshfunctor != functor) {
        m_meshfunctor = functor;
    }
}

void PhysicsMesh::sceneChangeEvent(const Qt3D::QSceneChangePtr &e){
    switch (e->type()) {
        case Qt3D::NodeUpdated: {
            Qt3D::QScenePropertyChangePtr propertyChange = qSharedPointerCast<Qt3D::QScenePropertyChange>(e);
            if (propertyChange->propertyName() == QByteArrayLiteral("meshFunctor")){ // Mesh with source
                setMeshFunctor(propertyChange->value().value<Qt3D::QAbstractMeshFunctorPtr>());
                m_dirty=true;
            }
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            break;
        }
        default:
            break;
    }
}


PhysicsMeshFunctor::PhysicsMeshFunctor(PhysicsManager* manager)
{
    m_manager=manager;
}


Qt3D::QBackendNode *PhysicsMeshFunctor::create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory)
const {
    PhysicsMesh* mesh=new PhysicsMesh();
    m_manager->m_resources.insert(frontend->id(),mesh);
    mesh->setFactory(factory);
    mesh->setManager(m_manager);
    mesh->setPeer(frontend);
    return mesh;
}
Qt3D::QBackendNode *PhysicsMeshFunctor::get(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        return m_manager->m_resources.operator [](id);
    else
        return Q_NULLPTR;
}
void PhysicsMeshFunctor::destroy(const Qt3D::QNodeId &id) const
{
    if(m_manager->m_resources.contains(id))
        delete m_manager->m_resources.operator [](id);
}



}


