#ifndef PHYSICSCOLLITION
#define PHYSICSCOLLITION
#include "backend_global.h"
#include <Qt3DCore/QNodeId>
#include <QVector3D>

namespace Physics {

class BACKENDSHARED_EXPORT Collision{

public:
    Qt3D::QNodeId body1;
    Qt3D::QNodeId body2;
    QVector3D pointOnBody1;
    QVector3D pointOnBody2;
    QVector3D normalBody2;
    bool isNew;

};

inline bool operator==(const Collision& c1,const Collision& c2)
{
    return (c1.body1 == c2.body1 && c1.body2 == c2.body2
            && c1.pointOnBody1 == c2.pointOnBody1 && c1.pointOnBody2 == c2.pointOnBody2
            && c1.normalBody2 == c2.normalBody2);
}
inline uint qHash(const Collision &key, uint seed)
{
    return Qt3D::qHash(key.body1, seed) ^ Qt3D::qHash(key.body2, seed);
}


}
#endif // PHYSICSCOLLITION

