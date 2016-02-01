#ifndef PHYSICSCOLLISION
#define PHYSICSCOLLISION
#include "qtphysicsunofficial_global.h"
#include <QVector3D>

namespace Physics {

class QTPHYSICSUNOFFICIAL_EXPORT Collision{

public:

    Qt3DCore::QNodeId body1;
    Qt3DCore::QNodeId body2;
    QVector3D pointOnBody1;
    QVector3D pointOnBody2;    
    QVector3D pointOnBody1Local;
    QVector3D pointOnBody2Local;
    QVector3D normalBody2;
    bool isNew;

    void swapBodies(){
        /**TODO: Swapping the normal???*/
        Qt3DCore::QNodeId tmp=this->body1;
        QVector3D tmp_v1=this->pointOnBody1;
        this->body1=this->body2;
        this->pointOnBody1=this->pointOnBody2;
        this->body2=tmp;
        this->pointOnBody2=tmp_v1;
    }

};

inline bool operator==(const Collision& c1,const Collision& c2)
{
    return (
                (
                 (c1.body1 == c2.body1 && c1.body2 == c2.body2 && c1.pointOnBody1 == c2.pointOnBody1 && c1.pointOnBody2 == c2.pointOnBody2)
                 ||
                 (c1.body1 == c2.body2 && c1.body2 == c2.body1 && c1.pointOnBody1 == c2.pointOnBody2 && c1.pointOnBody2 == c2.pointOnBody1)
                 )
             && c1.normalBody2 == c2.normalBody2);
}
inline uint qHash(const Collision &key, uint seed)
{
    return Qt3DCore::qHash(key.body1, seed) ^ Qt3DCore::qHash(key.body2, seed);
}


}
#endif // PHYSICSCOLLISION

