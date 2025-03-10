#ifndef Py_GEOMPY_H
#define Py_GEOMPY_H
/* Since this is a "meta-include" file, no #ifdef __cplusplus / extern "C" { */

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <patchlevel.h>

#if 3 <= PY_MAJOR_VERSION < 4 && 6 <= PY_MINOR_VERSION <= 10
#       define MINGW32_SUPPORT_NEED
#endif

#if defined(__MINGW32__) && defined(MINGW32_SUPPORT_NEED)
#       define MINGW32_DLL
#       define GPy_IMPORTED_SYMBOL __attribute__ ((dllimport))
#       define GPy_EXPORTED_SYMBOL __attribute__ ((dllexport))
#       define GPy_LOCAL_SYMBOL
#endif

#if defined(Py_ENABLE_SHARED) || defined(__MINGW32__)
#   if defined(MINGW32_DLL)
#       if defined(Py_BUILD_CORE) && !defined(Py_BUILD_CORE_MODULE)
#           define GPyAPI_FUNC(RTYPE) GPy_EXPORTED_SYMBOL RTYPE
#           define GPyAPI_DATA(RTYPE) extern GPy_EXPORTED_SYMBOL RTYPE
#           if defined(__MINGW32__)
#               define GPyMODINIT_FUNC GPy_EXPORTED_SYMBOL PyObject*
#           else /* __MINGW32__ */
#               define GPyMODINIT_FUNC PyObject*
#           endif /* __MINGW32__ */
#       else /* Py_BUILD_CORE */
#           if !defined(__MINGW32__)
#               define GPyAPI_FUNC(RTYPE) Py_IMPORTED_SYMBOL RTYPE
#               define GPyAPI_DATA(RTYPE) extern GPy_IMPORTED_SYMBOL RTYPE
#           else
#               define GPyAPI_FUNC(RTYPE) GPy_EXPORTED_SYMBOL RTYPE
#               define GPyAPI_DATA(RTYPE) extern GPy_EXPORTED_SYMBOL RTYPE
#           endif /* !__MINGW32__ */
/* module init functions outside the core must be exported */
#           if defined(__cplusplus)
#               define GPyMODINIT_FUNC extern "C" GPy_EXPORTED_SYMBOL PyObject*
#           else /* __cplusplus */
#               define GPyMODINIT_FUNC GPy_EXPORTED_SYMBOL PyObject*
#           endif /* __cplusplus */
#       endif /* Py_BUILD_CORE */
#   endif /* MINGW32_DLL */
#endif /* MINGW32_DLL */

#include <pyport.h>

#ifndef GPyAPI_FUNC
#       define GPyAPI_FUNC(RTYPE) PyAPI_FUNC(RTYPE)
#endif
#ifndef GPyAPI_DATA
#       define GPyAPI_DATA(RTYPE) PyAPI_DATA(RTYPE)
#endif
#ifndef GPyMODINIT_FUNC
#       define GPyMODINIT_FUNC PyMODINIT_FUNC
#endif

#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "polygonobject.h"
#include "_geompy.h"

#include "c/_math.h"

#endif /* !Py_GEOMPY_H */
