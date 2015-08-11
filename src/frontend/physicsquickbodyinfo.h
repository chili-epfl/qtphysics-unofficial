#ifndef PHYSICSQUICKBODYINFO_H
#define PHYSICSQUICKBODYINFO_H
#include <QObject>
#include "frontend_global.h"

namespace Physics {

class PhysicsBodyInfo;

class FRONTENDSHARED_EXPORT PhysicsQuickBodyInfo : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsQuickBodyInfo(QObject* parent=0);
};

}

#endif // PHYSICSQUICKBODYINFO_H
