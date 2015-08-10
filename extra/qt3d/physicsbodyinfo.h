#ifndef PHYSICSBODYINFO_H
#define PHYSICSBODYINFO_H
#include <Qt3DCore/QComponent>

namespace Physics {


class PhysicsBodyInfo: public Qt3D::QComponent
{
    Q_OBJECT
public:
    explicit PhysicsBodyInfo(Qt3D::QNode * parent=0);

signals:

public slots:

};

}
#endif // PHYSICSBODYINFO_H
