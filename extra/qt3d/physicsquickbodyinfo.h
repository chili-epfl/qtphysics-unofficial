#ifndef PHYSICSQUICKBODYINFO_H
#define PHYSICSQUICKBODYINFO_H
#include <QObject>

namespace Physics {

class PhysicsBodyInfo;

class PhysicsQuickBodyInfo : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsQuickBodyInfo(QObject* parent=0);
};

}

#endif // PHYSICSQUICKBODYINFO_H
