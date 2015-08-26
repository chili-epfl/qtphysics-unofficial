#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include "abstractbody.h"
#include <QVector3D>

namespace Physics {

namespace Bullet {

class BoxShape: public AbstractBody
{
    Q_OBJECT
public:
    explicit BoxShape(QObject* parent=0);
    ~BoxShape();

    QVector3D dimension(){return m_dimension;}
    void setDimension(QVector3D dimention);
protected:
    virtual void initShape();
private:
    QVector3D m_dimension;

};

}

}
#endif // BOXSHAPE_H
