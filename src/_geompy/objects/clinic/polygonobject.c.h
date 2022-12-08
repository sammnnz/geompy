/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(polygon_is_inner_point__doc__,
"is_inner_point($self, /, point)\n"
"--\n"
"\n"
"  point\n"
"    Point for which we determine where it lies relative to the polygon.\n"
"\n"
"Returns\n"
"\n"
"True if:\n"
"1. point is vertical of polygon;\n"
"2. point lies on the boundary of the polygon;\n"
"3. point lies inside the polygon.\n"
"\n"
"else False (point lies outside the polygon).");

#define POLYGON_IS_INNER_POINT_METHODDEF    \
    {"is_inner_point", (PyCFunction)(void(*)(void))polygon_is_inner_point, METH_FASTCALL|METH_KEYWORDS, polygon_is_inner_point__doc__},

static PyObject *
polygon_is_inner_point_impl(PyPolygonObject *self, PyObject *point);

static PyObject *
polygon_is_inner_point(PyPolygonObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"point", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "is_inner_point", 0};
    PyObject *argsbuf[1];
    PyObject *point;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    point = args[0];
    return_value = polygon_is_inner_point_impl(self, point);

exit:
    return return_value;
}
/*[clinic end generated code: output=2615237772439213 input=a9049054013a1b77]*/
