#ifndef OPTIONF_GLOBAL_H
#define OPTIONF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OPTIONF_LIBRARY)
#  define OPTIONFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OPTIONFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OPTIONF_GLOBAL_H
