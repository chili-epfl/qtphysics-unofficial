#include "physicsmesh.h"

#include "../physicsmanager.h"
#include <Qt3DRenderer>

namespace Physics {

PhysicsMesh::PhysicsMesh():
    Qt3D::QBackendNode(),
    m_dirty(false),
    m_enabled(false),
    m_meshfunctor(),
    m_objectName()

{
    m_manager=Q_NULLPTR;
}

void PhysicsMesh::setManager(PhysicsManager *manager){
        m_manager=manager;
}

PhysicsManager* PhysicsMesh::manager(){
    return m_manager;
}

PhysicsMesh::~PhysicsMesh(){
    m_manager->m_resources.remove(peerUuid());
}

void PhysicsMesh::updateFromPeer(Qt3D::QNode *peer){
    Qt3D::QAbstractMesh *mesh = static_cast<Qt3D::QAbstractMesh*>(peer);
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
            if (propertyChange->propertyName() == QByteArrayLiteral("meshFunctor")) // Mesh with source
                setMeshFunctor(propertyChange->value().value<Qt3D::QAbstractMeshFunctorPtr>());
            else if (propertyChange->propertyName() == QByteArrayLiteral("enabled"))
                m_enabled = propertyChange->value().toBool();
            m_dirty=true;
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


