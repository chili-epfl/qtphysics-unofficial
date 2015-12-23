#ifndef FRONTEND_GLOBAL_H
#define FRONTEND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FRONTEND_LIBRARY)
#  define FRONTENDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FRONTENDSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <Qt3DCore>
#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
#include <Qt3DRender>
#else
#include <Qt3DRenderer>
#endif


#endif // FRONTEND_GLOBAL_H
