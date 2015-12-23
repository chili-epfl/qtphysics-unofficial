#include "debugjob.h"
#include "../physicsmanager.h"
#include "../backendtypes/physicsentity.h"
#include "../backendtypes/physicsgeometryrenderer.h"
#include "../backendtypes/physicsgeometry.h"
#include "../backendtypes/physicsattribute.h"
#include "../backendtypes/physicsbuffer.h"

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

void DebugJob::print(Qt3DCore::QNodeId id){
    if(id.isNull()) return;
    PhysicsEntity* e= static_cast<PhysicsEntity*>(m_manager->m_resources.operator [](id));
    qDebug()<< e->objectName();
    if(!e->geometry_renderer().isNull()){
        PhysicsGeometryRenderer* gr= static_cast<PhysicsGeometryRenderer*>(m_manager->m_resources.operator [](e->geometry_renderer()));
        if(!gr->m_geometry.isNull()){
            PhysicsGeometry* g=static_cast<PhysicsGeometry*>(m_manager->m_resources.operator [](gr->m_geometry));
            Q_FOREACH(Qt3DCore::QNodeId att, g->attributes()){
                PhysicsAttribute* a=static_cast<PhysicsAttribute*>(m_manager->m_resources.operator [](att));
                if(a->objectName()=="vertexPosition"){
                   qDebug()<<a->asVector3D();
                }
            }
        }
    }
    for(Qt3DCore::QNodeId childId : e->childrenIds())
        print(childId);
}

}
