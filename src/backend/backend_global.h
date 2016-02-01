#ifndef BACKEND_GLOBAL_H
#define BACKEND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BACKEND_LIBRARY)
#  define BACKENDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BACKENDSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <Qt3DCore>
#include <Qt3DRender>


#endif // BACKEND_GLOBAL_H
