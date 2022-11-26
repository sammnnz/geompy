/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(_geompy_generate_random_polygon__doc__,
"generate_random_polygon($module, center, radius=1.0, verts_num=3, /)\n"
"--\n"
"\n"
"Implementation of generate_random_polygon.");

#define _GEOMPY_GENERATE_RANDOM_POLYGON_METHODDEF    \
    {"generate_random_polygon", (PyCFunction)(void(*)(void))_geompy_generate_random_polygon, METH_FASTCALL, _geompy_generate_random_polygon__doc__},

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

    if (!_PyArg_CheckPositional("generate_random_polygon", nargs, 1, 3)) {
        goto exit;
    }
    if (!PyTuple_Check(args[0])) {
        _PyArg_BadArgument("generate_random_polygon", "argument 1", "tuple", args[0]);
        goto exit;
    }
    center = args[0];
    if (nargs < 2) {
        goto skip_optional;
    }
    if (PyFloat_CheckExact(args[1])) {
        radius = PyFloat_AS_DOUBLE(args[1]);
    }
    else
    {
        radius = PyFloat_AsDouble(args[1]);
        if (radius == -1.0 && PyErr_Occurred()) {
            goto exit;
        }
    }
    if (nargs < 3) {
        goto skip_optional;
    }
    if (PyFloat_Check(args[2])) {
        PyErr_SetString(PyExc_TypeError,
                        "integer argument expected, got float" );
        goto exit;
    }
    verts_num = (unsigned int)PyLong_AsUnsignedLongMask(args[2]);
    if (verts_num == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
skip_optional:
    return_value = _geompy_generate_random_polygon_impl(module, center, radius, verts_num);

exit:
    return return_value;
}
/*[clinic end generated code: output=6ca33fa4d03d196a input=a9049054013a1b77]*/
