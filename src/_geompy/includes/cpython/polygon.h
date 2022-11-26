#ifndef Py_CPYTHON_POLYGON_H
#  error "this header file must not be included directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>

struct PyPolygonObject {
	PyObject_HEAD
	double* _verts;
	PyObject* verts;
};

/* Polygon object type */

PyAPI_DATA(PyTypeObject) PyPolygon_Type;

#define PyPolygon_CheckExact(op) Py_IS_TYPE(op, &PyPolygon_Type)


/* Public interface */

PyAPI_FUNC(PyObject*) PyPolygon_New(PyTypeObject* subtype, PyObject* args, PyObject* kwargs);
PyAPI_FUNC(PyObject*) PyPolygon_IsInnerPoint(PyPolygonObject* self, PyObject* point);


/* Internal interface */

PyAPI_FUNC(void) _PyPolygon_Dealloc(PyPolygonObject* self);
PyAPI_FUNC(int) _PyPolygon_Init(PyPolygonObject* self, PyObject* args);

#ifdef __cplusplus
}
#endif