#ifndef Py_CPYTHON_POLYGON_H
#  error "this header file must not be included directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

PyAPI_FUNC(void) _PyPolygon_Dealloc(PyPolygonObject* self);
PyAPI_FUNC(int) _PyPolygon_Init(PyPolygonObject* self, PyObject* args);

#ifdef __cplusplus
}
#endif