#ifndef GEOMPY_H
#define GEOMPY_H
#ifdef __cplusplus
extern "C" {
#endif

/* Public API */

PyAPI_FUNC(PyObject*) GeomPy_GenerateRandomPolygon(PyObject* module, PyObject* center, double radius, unsigned int verts_num);


/* Private API */

#ifndef Py_LIMITED_API
#  define Py_CPYTHON_GEOMPY_H
#  include  "cpython/geompy.h"
#  undef Py_CPYTHON_GEOMPY_H
#endif

#ifdef __cplusplus
}
#endif
#endif // !_GEOMPY_H_