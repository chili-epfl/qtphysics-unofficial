#include "physicsquickbodyinfo.h"
#include "physicsbodyinfo.h"
namespace Physics {

PhysicsQuickBodyInfo::PhysicsQuickBodyInfo(QObject* parent)
     : QObject(parent)
{
     Q_ASSERT(qobject_cast<PhysicsBodyInfo*>(parent) != Q_NULLPTR);
}

}
