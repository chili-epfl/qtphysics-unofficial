#ifndef COMPOUNDSHAPE_H
#define COMPOUNDSHAPE_H

#include "abstractbody.h"
namespace Bullet {


class CompoundShape: public AbstractCollitionShape
{
public:
    CompoundShape(QQuickItem* parent=0);
    ~CompoundShape();

    void setFallInertia(QVector3D fallInertia);
    void setMass(qreal mass);
    void addChildShapes(QList<btCollisionShape*> shapes);
private:
    void init();
    void clear();
};

}
#endif // COMPOUNDSHAPE_H
