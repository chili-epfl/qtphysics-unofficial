#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include "abstractbody.h"

namespace Physics {


namespace Bullet {

class SphereShape: public AbstractBody
{
    Q_OBJECT

public:
    SphereShape(QObject* parent=0);
    ~SphereShape();
    qreal radius(){return m_radius;}
    void setRadius(qreal radius);
protected:
    virtual void initShape();

private:

    qreal m_radius;
};

}}
#endif // SPHERESHAPE_H
