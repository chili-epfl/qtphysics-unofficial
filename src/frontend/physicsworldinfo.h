#ifndef PhysicsWorldInfo_H
#define PhysicsWorldInfo_H
#include <qtphysicsunofficial_global.h>


#include <QVector3D>

namespace Physics {

struct PhysicsWorldInfoData
{
    QVector3D m_gravity;
    qreal m_scaleFactor;
};


class QTPHYSICSUNOFFICIAL_EXPORT PhysicsWorldInfo:
        public Qt3DCore::QComponent
{
    Q_OBJECT
    Q_PROPERTY(QVector3D gravity READ gravity WRITE setGravity NOTIFY gravityChanged)
    Q_PROPERTY(qreal scaleFactor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged)
public:
    explicit PhysicsWorldInfo(QNode* parent=0);
    ~PhysicsWorldInfo();
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change) Q_DECL_OVERRIDE;

    QVector3D gravity() const {return m_gravity;}
    void setGravity(QVector3D gravity);

    qreal scaleFactor() const{return m_scaleFactor;}
    void setScaleFactor(qreal val);


    bool debug(){return m_debug;}
    void setDebug(bool debug){if(debug!=m_debug){m_debug=debug;emit debugChanged(m_debug);}}
signals:
    void gravityChanged();
    void debugChanged(bool debug);
    void scaleFactorChanged();
private:

    Qt3DCore::QNodeCreatedChangeBasePtr createNodeCreationChange() const Q_DECL_OVERRIDE;

    QVector3D m_gravity;
    bool m_debug;
    qreal m_scaleFactor;

};

}
#endif // PhysicsWorldInfo_H
