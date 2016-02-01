#ifndef PhysicsWorldInfo_H
#define PhysicsWorldInfo_H
#include "qtphysicsunofficial_global.h"


#include <QVector3D>

namespace Physics {


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsWorldInfo:
        public Qt3DCore::QComponent
{
    Q_OBJECT
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity NOTIFY gravityChanged)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)
public:
    explicit PhysicsWorldInfo(QNode* parent=0);
    ~PhysicsWorldInfo();
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change) Q_DECL_OVERRIDE;
    void copy(const QNode *ref) Q_DECL_OVERRIDE;

    QVector3D gravity() const {return m_gravity;}
    void setGravity(QVector3D gravity);

    bool debug(){return m_debug;}
    void setDebug(bool debug){if(debug!=m_debug){m_debug=debug;emit debugChanged(m_debug);}}
signals:
    void gravityChanged(QVector3D gravity);
    void debugChanged(bool debug);
private:
    QVector3D m_gravity;
    bool m_debug;
    QT3D_CLONEABLE(PhysicsWorldInfo)

};

}
#endif // PhysicsWorldInfo_H
