#ifndef AL808_GLOBAL_H
#define AL808_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AL808_LIBRARY)
#  define AL808SHARED_EXPORT Q_DECL_EXPORT
#else
#  define AL808SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AL808_GLOBAL_H
