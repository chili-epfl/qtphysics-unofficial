#ifndef BACKEND_GLOBAL_H
#define BACKEND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BACKEND_LIBRARY)
#  define BACKENDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BACKENDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BACKEND_GLOBAL_H
