/* Polygon description */

#ifndef Py_POLYGON_H
#define Py_POLYGON_H
#ifdef __cplusplus
extern C{
#endif

typedef struct PyPolygonObject PyPolygonObject;

struct PyPolygonObject {
	PyObject_HEAD
		double* _verts;
	PyObject* verts;
};

/* Polygon object type */

PyAPI_DATA(PyTypeObject) PyPolygon_Type;

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 9
#  define PyPolygon_CheckExact(op) Py_IS_TYPE(op, &PyPolygon_Type)
#else
#  define PyPolygon_CheckExact(op) (Py_TYPE(op) == &PyPolygon_Type)
#endif


/* Public API */

PyAPI_FUNC(PyObject*) PyPolygon_New(PyTypeObject* subtype, PyObject* args, PyObject* kwargs);
PyAPI_FUNC(PyObject*) PyPolygon_IsInnerPoint(PyPolygonObject* self, PyObject* point);

/* Private API */

#ifndef Py_LIMITED_API
#  define Py_CPYTHON_POLYGON_H
#  include  "cpython/polygon.h"
#  undef Py_CPYTHON_POLYGON_H
#endif

#ifdef __cplusplus
}
#endif
#endif // !Py_POLYGON_H
