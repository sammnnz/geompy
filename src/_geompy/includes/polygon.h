/* Polygon description */

#ifndef Py_POLYGON_H
#define Py_POLYGON_H
#ifdef __cplusplus
extern C{
#endif

typedef struct PyPolygonObject PyPolygonObject;

#ifndef Py_LIMITED_API
#  define Py_CPYTHON_POLYGON_H
#  include  "cpython/polygon.h"
#  undef Py_CPYTHON_POLYGON_H
#endif

#ifdef __cplusplus
}
#endif
#endif // !Py_POLYGON_H
