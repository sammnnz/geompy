/*
* GeomPy Module Description
*/
#include "_geompy.h"
#include "includes/polygon.h"
#include "includes/rand.h"
#include <math.h>
#include <stdlib.h>
#include "clinic/_geompy.c.h"
#include "includes/_math.h"

/*[clinic input]
module _geompy
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=47d63e40a3369661]*/

static int _grp_Compare(const void* a, const void* b)
{
	double** a_;
	double** b_;

	a_ = (double**)a;
	b_ = (double**)b;

	if (**a_ == **b_) {
		if (**(a_ + 1) == **(b_ + 1)) return 0;
		return **(a_ + 1) > **(b_ + 1) ? 1 : -1;
	}

	return **a_ > **b_ ? 1 : -1;
};

#define _GRP_MEMORY_CLEAR(i, list) \
	while (i) { \
		i--; \
		free(list[i]); \
	} \
	\
	free(list);

#define _GRP_MOD180_DEGREES(d) \
	(d < 180.0 ? d : d - 180.0)

/*[clinic input]
_geompy.generate_random_polygon

    center: object(subclass_of='&PyTuple_Type')
    radius: double = 1.0
    verts_num: unsigned_int(bitwise=True) = 3
    /

Implementation of generate_random_polygon.

[clinic start generated code]*/

static PyObject *
_geompy_generate_random_polygon_impl(PyObject *module, PyObject *center,
                                     double radius, unsigned int verts_num)
/*[clinic end generated code: output=7cb2ffc9bfb2bd4d input=49274a8864cba512]*/
{
	double x;
	double y;
	double** polars;
	unsigned short indicator;
	unsigned int vnum;
	PyObject* args;
	PyObject* polygon;
	PyObject* tmp_list;
	PyObject* tmp_tuple;

	if (verts_num < 3) {
		PyErr_SetString(PyExc_TypeError,
			"verts_num must be greater than or equal to three");

		return NULL;
	}

	if (!PyArg_ParseTuple(center, "dd:generate_random_polygon", &x, &y)) {
		PyErr_SetString(PyExc_TypeError,
			"argument parse error");

		return NULL;
	}

	polars = (double**)malloc(sizeof(double*) * verts_num);
	if (!polars) {
		goto memory_failed;
	}

	indicator = 1;
	for (unsigned int ui = 0; ui < verts_num; ui++) {
		polars[ui] = (double*)malloc(sizeof(double) * 2);
		if (!polars[ui]) {
			_GRP_MEMORY_CLEAR(ui, polars)
			goto memory_failed;
		}

		polars[ui][0] = random_angle(0);
		polars[ui][1] = random(0, radius);

		// if there are at least three points that 
		// do not lie on the same straight line, 
		// then the indicator will become equal to 0
		if (indicator && ui > 1) {
			if (_GRP_MOD180_DEGREES(polars[ui][0]) == _GRP_MOD180_DEGREES(polars[ui - 1][0])) {
				if (_GRP_MOD180_DEGREES(polars[ui][0]) != _GRP_MOD180_DEGREES(polars[ui - 2][0])) {
					indicator = 0;
				}
			}
			else {
				indicator = 0;
			}
		}

		// case of two equal points (repeat loop iteration)
		if (ui > 0) {
			if (polars[ui][0] == polars[ui - 1][0] && polars[ui][1] == polars[ui - 1][1]) {
				free(polars[ui]);
				ui--;
			}
		}
	}

	if (indicator) {
		vnum = verts_num;
		_GRP_MEMORY_CLEAR(vnum, polars)
		return _geompy_generate_random_polygon_impl(module, center, radius, verts_num);
	}
	
	qsort(polars, verts_num, sizeof(double*), _grp_Compare);
	tmp_list = Py_BuildValue("[]");
	while (verts_num) {
		verts_num--;

		PyList_Append(tmp_list, Py_BuildValue("(dd)", 
			x + polars[verts_num][1] * cos(polars[verts_num][0]), y + polars[verts_num][1] * sin(polars[verts_num][0])));

		free(polars[verts_num]);
	};

	free(polars);
	args = PyList_AsTuple(tmp_list);
	Py_DECREF(tmp_list);
	tmp_tuple = Py_BuildValue("()");
	polygon = PyPolygon_New(&PyPolygon_Type, tmp_tuple, tmp_tuple);
	_PyPolygon_Init(polygon, args);
	Py_DECREF(args);
	Py_DECREF(tmp_tuple);

	return polygon;

memory_failed:
	PyErr_SetString(PyExc_MemoryError,
		"malloc error");

	return NULL;
};

PyObject*
GeomPy_GenRandomPolygon(PyObject* module, PyObject* center, double radius, unsigned int verts_num) {
	return _geompy_generate_random_polygon_impl(module, center, radius, verts_num);
};

PyDoc_STRVAR(_geompy__doc__,
	"GeomPy: Python/C API module for geometric calculations");

static PyMethodDef _geompy_methods[] = {
	_GEOMPY_GENERATE_RANDOM_POLYGON_METHODDEF
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef _geompy_module = {
	PyModuleDef_HEAD_INIT,
	"_geompy",
	_geompy__doc__,
	-1,
	_geompy_methods
};

PyMODINIT_FUNC
PyInit__geompy(void) {
	PyObject* module = PyModule_Create(&_geompy_module);

	if (PyType_Ready(&PyPolygon_Type) < 0) {
		Py_XDECREF(module);
		return NULL;
	}

	Py_INCREF(&PyPolygon_Type);
	PyModule_AddObject(module, PyPolygon_Type.tp_name, (PyObject*)&PyPolygon_Type);

	return module;
}