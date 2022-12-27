/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(_geompy_polygon_is_inner_point__doc__,
"is_inner_point($self, /, point)\n"
"--\n"
"\n"
"Returns\n"
"\n"
"  point\n"
"    Point for which we determine where it lies relative to the polygon.\n"
"\n"
"True if:\n"
"1. point is vertical of polygon;\n"
"2. point lies on the boundary of the polygon;\n"
"3. point lies inside the polygon.\n"
"\n"
"else False (point lies outside the polygon).");

#define _GEOMPY_POLYGON_IS_INNER_POINT_METHODDEF    \
    {"is_inner_point", (PyCFunction)_geompy_polygon_is_inner_point, METH_FASTCALL|METH_KEYWORDS, _geompy_polygon_is_inner_point__doc__},

static PyObject *
_geompy_polygon_is_inner_point_impl(PyPolygonObject *self, PyObject *point);

static PyObject *
_geompy_polygon_is_inner_point(PyPolygonObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"point", NULL};
    static _PyArg_Parser _parser = {"O:is_inner_point", _keywords, 0};
    PyObject *point;

    if (!_PyArg_ParseStackAndKeywords(args, nargs, kwnames, &_parser,
        &point)) {
        goto exit;
    }
    return_value = _geompy_polygon_is_inner_point_impl(self, point);

exit:
    return return_value;
}
/*[clinic end generated code: output=1e11ad0add9d93fd input=a9049054013a1b77]*/
