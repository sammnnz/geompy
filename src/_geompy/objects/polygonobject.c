/* Polygon Object Module Description */

#include "../includes/polygon.h"
#include <structmember.h>
#include "clinic/polygonobject.c.h"
#include "../includes/_math.h"

/*[clinic input]
class polygon "PyPolygonObject *" "&PyPolygon_Type"
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=afa59843565ccc12]*/

PyDoc_STRVAR(polygon_doc,
    "Polygon object class.\n\
\n\
Typical use:\n\
>>> polygon((1, 2, 3), (4, 5, 6), (7, 8, 9))");

#define NONPy_CLEAR(op) \
    free(op); \
    op = NULL;

/*
* Clear attributes ( use when PyPolygon_Type include Py_TPFLAGS_HAVE_GC flag )
*/
static int
polygon_clear(PyPolygonObject* self) {
    NONPy_CLEAR(self->_verts);
    Py_CLEAR(self->verts);
    return 0;
}

/*
* Destroy PyPolygonObject
*/
static void
polygon_dealloc(PyPolygonObject* self) {
    Py_TRASHCAN_BEGIN(self, polygon_dealloc);

    PyObject_GC_UnTrack(self);
    NONPy_CLEAR(self->_verts);
    Py_CLEAR(self->verts);
    PyObject_GC_Del(self);

    Py_TRASHCAN_END;
}

/*
* Create instance of PyPolygonObject
*/
static int
polygon_init(PyPolygonObject* self, PyObject* args) {
    double x;
    double y;
    double* _verts;
    Py_ssize_t a_size;
    Py_ssize_t i;
    PyObject* tmp_list = NULL;
    PyObject* tmp_tuple = NULL;
    PyObject* verts;

    if (!PyTuple_CheckExact(args)) {
        return -1;
    }

    a_size = PyTuple_Size(args);
    self->_verts = (double*)malloc(sizeof(double) * 2);
    if (!self->_verts) {
        goto memory_failed;
    }

    tmp_list = Py_BuildValue("[]");
    i = 0;
    while (a_size > i) {
        tmp_tuple = PyTuple_GetItem(args, i);
        if (!PyTuple_Check(tmp_tuple)) {
            free(self->_verts);

            if (i < 2) {
                goto parse_failed;
            }

            break;
        }

        i++;
        _verts = (double*)realloc(self->_verts, sizeof(double) * 2 * i);
        if (!_verts) {
            goto memory_failed;
        }

        self->_verts = _verts;

        if (!PyArg_ParseTuple((PyTupleObject*)tmp_tuple, "dd:polygon_init", &x, &y)) {
            free(self->_verts);
            goto parse_failed;
        }

        self->_verts[2 * i - 2] = x;
        self->_verts[2 * i - 1] = y;
        PyList_Append(tmp_list, tmp_tuple);
    }

    if (i < 3) {
        free(self->_verts);
        goto parse_failed;
    }

    verts = PyList_AsTuple(tmp_list);
    self->verts = verts;

    Py_DECREF(tmp_list);
    return 0;

memory_failed:
    Py_XDECREF(tmp_list);
    PyErr_SetString(PyExc_MemoryError,
        "malloc error");

    return -1;

parse_failed:
    Py_DECREF(tmp_list);
    PyErr_SetString(PyExc_TypeError,
        "argument parse error");

    return -1;
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
    //Py_VISIT(self->_verts);
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
        PyErr_SetString(PyExc_OverflowError, "index overflow");
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

#define QUADRANT_NUM(verts, cq, x, y) \
if (verts == NULL) return NULL; \
if (verts + 1 == NULL) return NULL; \
if (*verts == x && *(verts + 1) == y) Py_RETURN_TRUE; /* vertical case */ \
if (*verts > x && *(verts + 1) >= y) cq = 0; \
else if (*_verts <= x && *(_verts + 1) > y) cq = 1; \
else if (*_verts < x && *(_verts + 1) <= y) cq = 2; \
else cq = 3;

# define WINDING_SUM(cq, v1, v2, x, y, wnum) \
    if (cq == 1) wnum += 1; \
    else if (cq == 3) wnum -= 1; \
    else if (cq == 2) wnum = PSEUDO_SCALAR_PRODUCT(v1, v2, x, y) > 0 ? wnum + 2 : wnum - 2; // BE CAREFUL: due to the calculation error,
                                                                                            // the pseudoscalar product may be zero

/*[clinic input]
polygon.is_inner_point
    
    point: 'O'
        Point for which we determine where it lies relative to the polygon.
 
Returns

True if:
1. point is vertical of polygon;
2. point lies on the boundary of the polygon;
3. point lies inside the polygon.

else False (point lies outside the polygon).
[clinic start generated code]*/

static PyObject*
polygon_is_inner_point_impl(PyPolygonObject* self, PyObject* point)
/*[clinic end generated code: output=1bd7346263dbb3a6 input=86d1e81a7c4b5eaf]*/
{
    double x;
    double y;
    double* _verts;
    short wnum; // winding number
    unsigned short curr_qdrnt = NULL;
    unsigned short first_qdrnt = NULL;
    unsigned short prev_qdrnt = NULL;
    Py_ssize_t po_size;

    if (!self->_verts && !self->verts) {
        PyErr_SetString(PyExc_TypeError,
            "null polygon object");

        return NULL;
    }

    po_size = PyTuple_Size(self->verts);
    if (po_size < 3) {
        PyErr_SetString(PyExc_TypeError,
            "polygon must contain at least 3 vertices");

        return NULL;
    }


    if (!PyArg_ParseTuple(point, "dd:is_inner_point", &x, &y)) {
        PyErr_SetString(PyExc_TypeError,
            "argument parse error");

        return NULL;
    }

    _verts = self->_verts;
    wnum = 0;
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

/*
* Polygon dealloc function for debug tests
*/
void
_PyPolygon_Dealloc(PyPolygonObject* self) {
    if (PyPolygon_CheckExact(self)) {
        polygon_dealloc(self);
    }
};

/*
* Polygon init function for debug tests
*/
int
_PyPolygon_Init(PyPolygonObject* self, PyObject* args) {
    if (!PyPolygon_CheckExact(self)) {
        return -1;
    }

    polygon_init(self, args);
    return 0;
};

PyObject*
PyPolygon_IsInnerPoint(PyPolygonObject* self, PyObject* point) {
    return polygon_is_inner_point_impl(self, point);
}

/*
* Public interface function polygon_new
*/
PyObject*
PyPolygon_New(PyTypeObject* subtype, PyObject* args, PyObject* kwargs) {
    return polygon_new(subtype, args, kwargs);
}

static PyMethodDef polygon_methods[] = {
    POLYGON_IS_INNER_POINT_METHODDEF
    {NULL}  /* Sentinel */
};

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
    0,                                      /* tp_version_tag */
    0,                                      /* tp_finalize */
    0                                       /* tp_vectorcall */
};