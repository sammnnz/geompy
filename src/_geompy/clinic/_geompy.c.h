/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(_geompy_generate_random_polygon__doc__,
"generate_random_polygon($module, center, radius=1.0, verts_num=3, /)\n"
"--\n"
"\n"
"Implementation of generate_random_polygon.");

#define _GEOMPY_GENERATE_RANDOM_POLYGON_METHODDEF    \
    {"generate_random_polygon", (PyCFunction)_geompy_generate_random_polygon, METH_FASTCALL, _geompy_generate_random_polygon__doc__},

static PyObject *
_geompy_generate_random_polygon_impl(PyObject *module, PyObject *center,
                                     double radius, unsigned int verts_num);

static PyObject *
_geompy_generate_random_polygon(PyObject *module, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    PyObject *center;
    double radius = 1.0;
    unsigned int verts_num = 3;

    if (!_PyArg_ParseStack(args, nargs, "O!|dI:generate_random_polygon",
        &PyTuple_Type, &center, &radius, &verts_num)) {
        goto exit;
    }
    return_value = _geompy_generate_random_polygon_impl(module, center, radius, verts_num);

exit:
    return return_value;
}
/*[clinic end generated code: output=62486541a551f4e8 input=a9049054013a1b77]*/
