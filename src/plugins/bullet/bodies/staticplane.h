#ifndef STATICPLANE_H
#define STATICPLANE_H

#include "abstractbody.h"
#include <QVector3D>

namespace Physics {

namespace Bullet {

class StaticPlane : public AbstractBody
{
    Q_OBJECT
public:
    explicit StaticPlane(QObject* parent=0);
    ~StaticPlane();
    QVector3D normal(){return m_normal;}
    void setNormal(QVector3D normal);
    qreal planeConstant(){return m_planeConstant;}
    void setPlaneConstant(qreal d);
    virtual void setMass(qreal m) Q_DECL_OVERRIDE;

public slots:

protected:
        void initShape();
private:

    QVector3D m_normal;
    qreal m_planeConstant;
};

}
}
#endif // STATICPLANE_H
