#ifndef HEIGHTFIELD2D_H
#define HEIGHTFIELD2D_H

#include "abstractbody.h"
#include <QVector3D>

namespace Physics {

namespace Bullet {

class HeightField2D : public AbstractBody
{
    Q_OBJECT
public:
    HeightField2D(QObject* parent=0);
    ~HeightField2D();
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
#endif // HEIGHTFIELD2D_H
