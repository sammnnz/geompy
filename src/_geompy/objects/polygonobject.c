/* Polygon object implementation */
#include <Python.h>
#include <structmember.h>              // PyMemberDef   T_OBJECT    READONLY

#include "Geompy.h"

/*[clinic input]
module _geompy
class _geompy.polygon "PyPolygonObject *" "&PyPolygon_Type"
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=3b980588babc08e9]*/

#include "clinic/polygonobject.c.h"

PyDoc_STRVAR(polygon_doc,
    "Polygon object class.\n\
\n\
Typical use:\n\
>>> polygon((1, 2), (4, 5), (7, 8))");

#define NonPy_CLEAR(op) \
    if (op != NULL) {   \
        free(op);       \
        op = NULL;      \
    }                   \

/*
* Clear attributes ( use when PyPolygon_Type include Py_TPFLAGS_HAVE_GC flag )
*/
static int
polygon_clear(PyPolygonObject* self) {
    NonPy_CLEAR(self->_verts);
    Py_CLEAR(self->verts);
    return 0;
}

/* Look like mypy */
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 8
#  define CPy_TRASHCAN_BEGIN(op, dealloc) Py_TRASHCAN_BEGIN(op, dealloc)
#  define CPy_TRASHCAN_END(op) Py_TRASHCAN_END
#else
#  define CPy_TRASHCAN_BEGIN(op, dealloc) Py_TRASHCAN_SAFE_BEGIN(op)
#  define CPy_TRASHCAN_END(op) Py_TRASHCAN_SAFE_END(op)
#endif

/*
* Destroy PyPolygonObject
*/
static void
polygon_dealloc(PyPolygonObject* self) {
    CPy_TRASHCAN_BEGIN(self, polygon_dealloc)

    PyObject_GC_UnTrack(self);
    NonPy_CLEAR(self->_verts);
    Py_CLEAR(self->verts);
    PyObject_GC_Del(self);

    CPy_TRASHCAN_END(self)
}

/*
* Create instance of PyPolygonObject
*/
static int
polygon_init(PyPolygonObject* self, PyObject* args, PyObject* kwargs) {
    double x, y;
    double* _verts;
    Py_ssize_t args_size, count;

    if (!PyTuple_CheckExact(args)) {
        PyErr_SetString(PyExc_TypeError,
            "Invalid arguments.");

        return -1;
    }

    args_size = PyTuple_Size(args);
    if (args_size < 3) {
        PyErr_SetString(PyExc_TypeError,
            "Polygon should be include not less 3 points.");
        
        return -1;
    }

    self->_verts = (double*)malloc(sizeof(double) * 2);
    if (!self->_verts) {
        PyErr_SetString(PyExc_MemoryError,
            "Malloc error.");

        return -1;
    }

    self->verts = PyTuple_New(args_size);
    count = 0;
    while (count < args_size) {
        PyObject* o;
        o = PyTuple_GetItem(args, count);
        PyTuple_SetItem(self->verts, count, o);
        Py_INCREF(o);
        if (!PyTuple_CheckExact(o)) {
            PyErr_SetString(PyExc_TypeError,
                "Every argument should be only tuple.");
            return -1;
        }

        count++;
        _verts = (double*)realloc(self->_verts, sizeof(double) * 2 * (size_t)count);
        if (!_verts) {
            PyErr_SetString(PyExc_MemoryError,
                "Malloc error.");
            return -1;
        }

        self->_verts = _verts;

        if (!PyArg_ParseTuple(o, "dd:polygon_init", &x, &y)) {
            PyErr_SetString(PyExc_TypeError,
                "Every point in polygon should be consist of 2 verticals. Every vertical should be only a real number.");
            return -1;
        }

        self->_verts[2 * count - 2] = x;
        self->_verts[2 * count - 1] = y;
    }

    return 0;
}

/*
* Create new empty PyPolygonObject
*/
static PyObject*
polygon_new(PyTypeObject* subtype, PyObject* args, PyObject* kwargs) {
    PyPolygonObject* op = PyObject_GC_New(PyPolygonObject, subtype);
    if (op == NULL) {
        return NULL;
    }

    op->_verts = NULL;
    op->verts = NULL;

    PyObject_GC_Track(op);
    return (PyObject*)op;
}

/*
* Detect reference cycles ( use when PyPolygon_Type include Py_TPFLAGS_HAVE_GC flag )
*/
static int
polygon_traverse(PyPolygonObject* self, visitproc visit, void* arg)
{
    Py_VISIT(self->verts);
    return 0;
}

/*
* Get vertical by index ( like __getitem__ for list )
*/
static PyObject*
polygon_subscript(PyPolygonObject* self, PyObject* index) {
    PyObject* item;
    Py_ssize_t ix;

    if (!PyLong_CheckExact(index)) {
        return NULL;
    }

    ix = PyLong_AsSsize_t(index);
    if (ix == -1 && PyErr_Occurred()) {
        PyErr_SetString(PyExc_OverflowError, "Index overflow.");
        return NULL;
    }

    item = PyTuple_GetItem(self->verts, ix);
    return item;
}

static PyMappingMethods polygon_as_mapping = {
    0,                                /*mp_length*/
    (binaryfunc)polygon_subscript,    /*mp_subscript*/
    0                                 /*mp_ass_subscript*/
};

PyDoc_STRVAR(polygon_verts_doc,
    " Tuple of polygon's verticals ");

#define OFF(x) offsetof(PyPolygonObject, x)

static PyMemberDef polygon_members[] = {
    {"verts", T_OBJECT, OFF(verts), READONLY, polygon_verts_doc},
    {NULL}
};

#define QUADRANT_NUM(verts, cq, x, y) /* warning: not safe for verts*/ \
if (*verts == x && *(verts + 1) == y) Py_RETURN_TRUE; /* vertical case */ \
if (*verts > x && *(verts + 1) >= y) cq = 0; \
else if (*_verts <= x && *(_verts + 1) > y) cq = 1; \
else if (*_verts < x && *(_verts + 1) <= y) cq = 2; \
else cq = 3;

// TODO: fix ubuntu gcc compiler error - undefined symbol: PSEUDO_SCALAR_PRODUCT
#ifndef PSEUDO_SCALAR_PRODUCT
#   define PSEUDO_SCALAR_PRODUCT(v1, v2, x, y) (*v2 - *v1) * (y - *(v1 + 1)) - (x - *v1) * (*(v2 + 1) - *(v1 + 1))
#endif

# define WINDING_SUM(cq, v1, v2, x, y, wnum) \
    if (cq == 1) wnum += 1; \
    else if (cq == 3) wnum -= 1; \
    else if (cq == 2) wnum = PSEUDO_SCALAR_PRODUCT(v1, v2, x, y) > 0 ? wnum + 2 : wnum - 2; // BE CAREFUL: due to the calculation error,
                                                                                            // the pseudoscalar product may be zero

/*[clinic input]
geompy.polygon.is_inner_point
    
    point: 'O'
        Point for which we determine where it lies relative to the polygon.
 
Returns

True if:
1. point is vertical of polygon;
2. point lies on the boundary of the polygon;
3. point lies inside the polygon.

else False (point lies outside the polygon).
[clinic start generated code]*/

static PyObject *
geompy_polygon_is_inner_point_impl(PyPolygonObject *self, PyObject *point)
/*[clinic end generated code: output=891bbb7fdf805b92 input=fb1658ba75c0b44d]*/
{
    double x, y;
    double* _verts;
    short wnum; // winding number
    unsigned short curr_qdrnt, first_qdrnt, prev_qdrnt;
    Py_ssize_t po_size;

    if (!self->_verts || !self->verts) {
        PyErr_SetString(PyExc_TypeError,
            "Null polygon object.");

        return NULL;
    }

    po_size = PyTuple_Size(self->verts);
    if (po_size < 3) {
        PyErr_SetString(PyExc_TypeError,
            "Polygon must contain >= 3 vertices.");

        return NULL;
    }


    if (!PyArg_ParseTuple(point, "dd:is_inner_point", &x, &y)) {
        PyErr_SetString(PyExc_TypeError,
            "Argument parse error.");

        return NULL;
    }

    _verts = self->_verts;
    wnum = 0;
    curr_qdrnt = 0;
    first_qdrnt = 0;
    prev_qdrnt = 0;
    QUADRANT_NUM(_verts, first_qdrnt, x, y);
    prev_qdrnt = first_qdrnt;
    po_size--;
    _verts++;
    _verts++;

    while (po_size)
    {
        QUADRANT_NUM(_verts, curr_qdrnt, x, y);
        curr_qdrnt = curr_qdrnt >= prev_qdrnt ? curr_qdrnt - prev_qdrnt : 4 + curr_qdrnt - prev_qdrnt; // ( [curr_qdrnt - prev_qdrnt] mod 4)
        WINDING_SUM(curr_qdrnt, (_verts - 2), _verts, x, y, wnum);
        prev_qdrnt = (curr_qdrnt + prev_qdrnt) % 4;
        po_size--;
        _verts++;
        _verts++;
    }

    curr_qdrnt = first_qdrnt >= prev_qdrnt ? first_qdrnt - prev_qdrnt : 4 + first_qdrnt - prev_qdrnt; // ( [first_qdrnt - prev_qdrnt] mod 4)
    WINDING_SUM(curr_qdrnt, (_verts - 2), (self->_verts), x, y, wnum);

    if (wnum) Py_RETURN_TRUE; // inside case (wnum = -4 or 4) and border case (wnum = -3, -2, -1, 1, 2, 3)

    Py_RETURN_FALSE; // outside case (wnum = 0)
}

static PyMethodDef polygon_methods[] = {
    GEOMPY_POLYGON_IS_INNER_POINT_METHODDEF
    {NULL}  /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 8
#  define ADDITIONAL_ATTRIBUTES(tp_version_tag, tp_finalize, tp_vectorcall) tp_version_tag, tp_finalize, tp_vectorcall
#else
#  define ADDITIONAL_ATTRIBUTES(tp_version_tag, tp_finalize, tp_vectorcall)
#endif

PyTypeObject PyPolygon_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "polygon",                              /* tp_name */
    sizeof(PyPolygonObject),                /* tp_basicsize */
    0,                                      /* tp_itemsize */
    (destructor)polygon_dealloc,            /* tp_dealloc */
    0,                                      /* tp_print */
    0,                                      /* tp_getattr */
    0,                                      /* tp_setattr */
    0,                                      /* tp_reserved */
    0,                                      /* tp_repr */
    0,                                      /* tp_as_number */
    0,                                      /* tp_as_sequence */
    &polygon_as_mapping,                    /* tp_as_mapping */
    0,                                      /* tp_hash  */
    0,                                      /* tp_call */
    0,                                      /* tp_str */
    0,                                      /* tp_getattro */
    0,                                      /* tp_setattro */
    0,                                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |  // default
    Py_TPFLAGS_BASETYPE | // inheritance support
    Py_TPFLAGS_HAVE_GC,   // garbage collection
                                            /* tp_flags */
    polygon_doc,                            /* tp_doc */
    (traverseproc)polygon_traverse,         /* tp_traverse */
    (inquiry)polygon_clear,                 /* tp_clear */
    0,                                      /* tp_richcompare */
    0,                                      /* tp_weaklistoffset */
    0,                                      /* tp_iter */
    0,                                      /* tp_iternext */
    polygon_methods,                        /* tp_methods */
    polygon_members,                        /* tp_members */
    0,                                      /* tp_getset */
    0,                                      /* tp_base */
    0,                                      /* tp_dict */
    0,                                      /* tp_descr_get */
    0,                                      /* tp_descr_set */
    0,                                      /* tp_dictoffset */
    (initproc)polygon_init,                 /* tp_init */
    0,                                      /* tp_alloc */
    (newfunc)polygon_new,                   /* tp_new */
    0,                                      /* tp_free */
    0,                                      /* tp_is_gc */
    0,                                      /* tp_bases */
    0,                                      /* tp_mro */
    0,                                      /* tp_cache */
    0,                                      /* tp_subclasses */
    0,                                      /* tp_weaklist */
    0,                                      /* tp_del */
    ADDITIONAL_ATTRIBUTES(0, 0, 0)
};

int
PyPolygon_Init(PyObject* self, PyObject* args) {
    if (!PyPolygon_CheckExact(self)) {
        // TODO
        return -1;
    }

    if (((PyPolygonObject*)self)->_verts != NULL || ((PyPolygonObject*)self)->verts != NULL) {
        return -1;
    }

    polygon_init(((PyPolygonObject*)self), args, NULL);
    return 0;
}

PyObject*
PyPolygon_New(void) {
    return polygon_new(&PyPolygon_Type, NULL, NULL);
}

PyObject*
PyPolygon_IsInnerPoint(PyObject* self, PyObject* point) {
    double x, y;

    if (!PyPolygon_CheckExact(self)) {
        // TODO
        return NULL;
    }

    if (!PyArg_ParseTuple(point, "dd:PyPolygon_IsInnerPoint", &x, &y)) {
        return NULL;
    }

    return geompy_polygon_is_inner_point_impl((PyPolygonObject*)self, point);
}

int
_PyPolygon_Dealloc(PyObject* self) {
    if (!PyPolygon_CheckExact(self)) {
        //TODO
        return -1;
    }

    polygon_dealloc((PyPolygonObject*)self);
    return 0;
}
