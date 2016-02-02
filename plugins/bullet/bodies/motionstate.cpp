#include <bodies/motionstate.h>
namespace Physics {


namespace Bullet{

MotionState::MotionState(QObject *parent) : QObject(parent),
    btDefaultMotionState()
{

}

MotionState::MotionState(const btTransform &startTrans, const btTransform &centerOfMassOffset,QObject* parent)
    :QObject(parent),btDefaultMotionState(startTrans,centerOfMassOffset)
{

}
MotionState::MotionState(const QMatrix4x4 startTrans, const QMatrix4x4 centerOfMassOffset,QObject* parent)
    :QObject(parent)
{
    btMatrix3x3 w_rotation(startTrans.operator ()(0,0),startTrans.operator ()(0,1),startTrans.operator ()(0,2),
                           startTrans.operator ()(1,0),startTrans.operator ()(1,1),startTrans.operator ()(1,2),
                           startTrans.operator ()(2,0),startTrans.operator ()(2,1),startTrans.operator ()(2,2));

    btVector3 w_translation(startTrans.operator ()(0,3),startTrans.operator ()(1,3),startTrans.operator ()(2,3));
    m_graphicsWorldTrans=btTransform(w_rotation,w_translation);
    btMatrix3x3 c_rotation(centerOfMassOffset.operator ()(0,0),centerOfMassOffset.operator ()(0,1),centerOfMassOffset.operator ()(0,2),
                           centerOfMassOffset.operator ()(1,0),centerOfMassOffset.operator ()(1,1),centerOfMassOffset.operator ()(1,2),
                           centerOfMassOffset.operator ()(2,0),centerOfMassOffset.operator ()(2,1),centerOfMassOffset.operator ()(2,2));
    btVector3 c_translation(centerOfMassOffset.operator ()(0,3),centerOfMassOffset.operator ()(1,3),centerOfMassOffset.operator ()(2,3));

    m_centerOfMassOffset=btTransform(c_rotation,c_translation);
    m_startWorldTrans=btTransform(m_graphicsWorldTrans);

}
void MotionState::setWorldTransform(const btTransform &centerOfMassWorldTrans){
    btDefaultMotionState::setWorldTransform(centerOfMassWorldTrans);
}
void MotionState::getWorldTransform(btTransform &centerOfMassWorldTrans) const{
    return btDefaultMotionState::getWorldTransform(centerOfMassWorldTrans);
}


void MotionState::setWorldTransform(QMatrix4x4 m){
    btMatrix3x3 w_rotation(m.operator ()(0,0),m.operator ()(0,1),m.operator ()(0,2),
                           m.operator ()(1,0),m.operator ()(1,1),m.operator ()(1,2),
                           m.operator ()(2,0),m.operator ()(2,1),m.operator ()(2,2));
    btVector3 w_translation(m.operator ()(0,3),m.operator ()(1,3),m.operator ()(2,3));
    btDefaultMotionState::setWorldTransform(btTransform(w_rotation,w_translation));
}

QMatrix4x4 MotionState::getWorldTransformAsQMatrix4x4(){
    btTransform matrix;
    getWorldTransform(matrix);
    btScalar* m=new btScalar[16];
    matrix.getOpenGLMatrix(m);
    QMatrix4x4 worldTranform(m[0],m[4],m[8],m[12],
                            m[1],m[5],m[9],m[13],
                            m[2],m[6],m[10],m[14],
                            m[3],m[7],m[11],m[15]);
    return worldTranform;
}

}}
