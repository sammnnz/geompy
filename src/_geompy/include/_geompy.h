#ifndef _GEOMPY_H
#define _GEOMPY_H
#ifdef __cplusplus
extern "C" {
#endif

/* Public API */

GPyAPI_FUNC(PyObject*) Geompy_GenerateRandomPolygon(PyObject* module, PyObject* center, double radius, unsigned int verts_num);


/* Private API */

#ifndef Py_LIMITED_API
#  define Py_CPYTHON__GEOMPY_H
#  include  "cpython/_geompy.h"
#  undef Py_CPYTHON__GEOMPY_H
#endif

#ifdef __cplusplus
}
#endif
#endif // !_GEOMPY_H