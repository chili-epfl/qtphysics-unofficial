#ifndef HEIGHTFIELD2D_H
#define HEIGHTFIELD2D_H

#include <QQuickItem>
#include "abstractbody.h"
#include <QVector3D>
namespace Bullet {

class HeightField2D : public AbstractCollitionShape
{
    Q_OBJECT
    Q_PROPERTY(QVector3D normal READ normal WRITE setNormal NOTIFY normalChanged)
    Q_PROPERTY(qreal planeConstant READ planeConstant WRITE setPlaneConstant NOTIFY planeConstantChanged)
public:
    HeightField2D(QQuickItem* parent=0);
    ~HeightField2D();
    QVector3D normal(){return m_normal;}
    void setNormal(QVector3D normal);
    qreal planeConstant(){return m_planeConstant;}
    void setPlaneConstant(qreal d);

    void setFallInertia(QVector3D fallInertia);
    void setMass(qreal mass);


signals:
    void normalChanged(QVector3D normal);
    void planeConstantChanged(qreal d);
public slots:

private:
    void init();
    void clear();


    QVector3D m_normal;
    qreal m_planeConstant;
};

}

#endif // HEIGHTFIELD2D_H
