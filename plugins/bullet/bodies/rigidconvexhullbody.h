#ifndef RigidConvexHullBody_H
#define RigidConvexHullBody_H
#include "abstractrigidbody.h"
namespace Physics {

namespace Bullet {

class RigidConvexHullBody : public AbstractRigidBody
{
    Q_OBJECT
public:
    explicit RigidConvexHullBody(QObject* parent=0);
    explicit RigidConvexHullBody(qreal* points,int n_points,QObject* parent=0);
    ~RigidConvexHullBody();
    void addPoint(QVector3D p);
    void updatePoints(qreal* points,int n_points);
protected:
    void initShape(qreal* points,int n_points);
    void initShape()Q_DECL_OVERRIDE;
private:
};

}}
#endif // RigidConvexHullBody_H
