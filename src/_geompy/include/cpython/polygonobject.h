#ifndef Py_CPYTHON_POLYGONOBJECT_H
#  error "this header file must not be included directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	PyObject_HEAD
		double* _verts;
	PyObject* verts;
} PyPolygonObject;

GPyAPI_FUNC(int) _PyPolygon_Dealloc(PyObject* self);

#ifdef __cplusplus
}
#endif