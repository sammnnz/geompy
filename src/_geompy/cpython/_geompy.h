#ifndef Py_CPYTHON__GEOMPY_H
#  error "this header file must not be included directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>

/* Public interface */

PyAPI_FUNC(PyObject*) GeomPy_GenRandomPolygon(PyObject* module, PyObject* center, double radius, unsigned int verts_num);

#ifdef __cplusplus
}
#endif