#include "debugdraw.h"
#include <QVector3D>
DebugDraw::DebugDraw():
    btIDebugDraw()
{

}

void DebugDraw::drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color){
    QString type="line";
    QVector3D p1(from.x(),from.y(),from.z());
    QVector3D p2(to.x(),to.y(),to.z());
    //debug_entities.append(type);
    debug_entities.append(p1);
    debug_entities.append(p2);
}
void DebugDraw::drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance,
                                  int lifeTime, const btVector3 &color){

}
void DebugDraw::reportErrorWarning (const char *warningString){

}
void DebugDraw::draw3dText (const btVector3 &location, const char *textString){

}
void DebugDraw::setDebugMode (int debugMode){

}
int DebugDraw::getDebugMode () const{
   return btIDebugDraw::DBG_DrawAabb;
}


