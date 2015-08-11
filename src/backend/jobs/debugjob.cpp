#include "debugjob.h"
#include "../physicsmanager.h"
#include "../backendtypes/physicsentity.h"
#include <QDebug>
namespace Physics {


DebugJob::DebugJob(PhysicsManager* manager):
    QAspectJob()
{
    m_manager=manager;
}

void DebugJob::run(){
    print(m_manager->rootEntityId());
    //qDebug()<<"End";
}

void DebugJob::print(Qt3D::QNodeId id){
    if(id.isNull()) return;
    PhysicsEntity* e= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](id));
//    qDebug()<< e->objectName();
  //  qDebug()<< e->objectName();
    for(PhysicsEntity* child : e->children())
        print(child->peerUuid());
}

}
