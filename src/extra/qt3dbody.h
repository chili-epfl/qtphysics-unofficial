#ifndef QT3DBODY_H
#define QT3DBODY_H

#include "src/CollitionShapes/boxshape.h"
#include "src/CollitionShapes/sphereshape.h"
#include "src/CollitionShapes/convexhullshape.h"
#include <Qt3DCore>
#include <Qt3DRenderer>
 #include <QFlags>

namespace Bullet {

class QT3DBody : public AbstractBody
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QEntity* entity READ entity WRITE setEntity NOTIFY entityChanged)
    Q_PROPERTY(Qt3D::QEntity* sceneRoot READ sceneRoot WRITE setSceneRoot NOTIFY sceneRootChanged)
    Q_PROPERTY(Options options READ options WRITE setOptions NOTIFY optionsChanged)

public:
    enum Option{
        INCLUDECHILDREN,
    };

    Q_DECLARE_FLAGS(Options, Option)

    QT3DBody(QQuickItem* parent=0);

    Qt3D::QEntity* entity(){return m_entity;}
    void setEntity(Qt3D::QEntity* entity,bool force=false);

    void setKinematic(bool kinematic){ setKinematic(kinematic,false);}
    void setKinematic(bool kinematic,bool force);

    Qt3D::QEntity* sceneRoot(){return m_sceneRoot;}
    void setSceneRoot(Qt3D::QEntity* entity);

    void setWorldTransformation(QMatrix4x4 m){setWorldTransformation(m,true);}
    void setWorldTransformation(QMatrix4x4 m,bool isFromProperty);
signals:
    void entityChanged();
    void sceneRootChanged();
    void optionsChanged();
public slots:

private:
    void init();
    void clean();

    btCollisionShape* generateSingleShape(Qt3D::QEntity *entity);
    btCollisionShape* generateCompoundShape(Qt3D::QEntity *entity);

    Qt3D::QEntity* m_entity;
    Qt3D::QEntity* m_sceneRoot;

    Options m_options;
    bool m_isWorldTransformationFromProperty;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(QT3DBody::Options)

}
#endif // QT3DBODY_H
