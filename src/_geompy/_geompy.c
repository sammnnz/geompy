/*
* GeomPy Module Description
*/
#include <Python.h>

#include "include/Geompy.h"

/*[clinic input]
module _geompy
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=47d63e40a3369661]*/

#include "clinic/_geompy.c.h"

static int grp_Compare(const void* a, const void* b)
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
}

#define GRP_MEMORY_CLEAR(i, list) \
	while (i) { \
		i--; \
		free(list[i]); \
	} \
	\
	free(list);

#define GRP_MOD180_DEGREES(d) \
	(d < 180.0 ? d : d - 180.0)

#ifndef M_PI
#	define M_PI 3.14159265358979323846   // pi
#endif

/*[clinic input]
geompy.generate_random_polygon

    center: object(subclass_of='&PyTuple_Type')
    radius: double = 1.0
    verts_num: unsigned_int(bitwise=True) = 3
    /

Implementation of generate_random_polygon.

[clinic start generated code]*/

static PyObject *
geompy_generate_random_polygon_impl(PyObject *module, PyObject *center,
                                     double radius, unsigned int verts_num)
/*[clinic end generated code: output=7cb2ffc9bfb2bd4d input=49274a8864cba512]*/
{
	double x, y;
	double** polars;
	unsigned short indicator;
	unsigned int vnum;
	PyObject* args;
	PyObject* polygon;

	if (verts_num < 3) {
		PyErr_SetString(PyExc_TypeError,
			"verts_num must be >= 3");

		return NULL;
	}

	if (!PyArg_ParseTuple(center, "dd:generate_random_polygon", &x, &y)) {
		PyErr_SetString(PyExc_TypeError,
			"Argument parse error: center must be 2d point.");

		return NULL;
	}

	polars = (double**)malloc(sizeof(double*) * verts_num);
	if (!polars) {
		goto memory_failed;
	}

	indicator = 1;
	srand((unsigned int)time(NULL));
	for (unsigned int ui = 0; ui < verts_num; ui++) {
		polars[ui] = (double*)malloc(sizeof(double) * 2);
		if (!polars[ui]) {
			GRP_MEMORY_CLEAR(ui, polars)
			goto memory_failed;
		}

		polars[ui][0] = 2.0 * M_PI * ((double)rand() / RAND_MAX);
		polars[ui][1] = radius * ((double)rand() / RAND_MAX);

		// if there are at least three points that 
		// do not lie on the same straight line, 
		// then the indicator will become equal to 0
		if (indicator && ui > 1) {
			if (GRP_MOD180_DEGREES(polars[ui][0]) == GRP_MOD180_DEGREES(polars[ui - 1][0])) {
				if (GRP_MOD180_DEGREES(polars[ui][0]) != GRP_MOD180_DEGREES(polars[ui - 2][0])) {
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
		GRP_MEMORY_CLEAR(vnum, polars)
		return geompy_generate_random_polygon_impl(module, center, radius, verts_num);
	}
	
	qsort(polars, verts_num, sizeof(double*), grp_Compare);
	args = PyTuple_New(verts_num);
	while (verts_num) {
		verts_num--;
		PyTuple_SetItem(args, verts_num, Py_BuildValue("(dd)",
			x + polars[verts_num][1] * cos(polars[verts_num][0]), y + polars[verts_num][1] * sin(polars[verts_num][0])));
		free(polars[verts_num]);
	};

	free(polars);
	polygon = PyPolygon_New();
	PyPolygon_Init(polygon, args);

	return polygon;

memory_failed:
	PyErr_SetString(PyExc_MemoryError,
		"Malloc error.");

	return NULL;
}

PyObject*
Geompy_GenerateRandomPolygon(PyObject* module, PyObject* center, double radius, unsigned int verts_num) {
	return geompy_generate_random_polygon_impl(module, center, radius, verts_num);
}

PyDoc_STRVAR(geompy__doc__,
	"_geompy: Python/C API module for geometric calculations");

static PyMethodDef geompy_methods[] = {
	GEOMPY_GENERATE_RANDOM_POLYGON_METHODDEF
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef geompy_module = {
	PyModuleDef_HEAD_INIT,	// m_base
	"_geompy",				// m_name
	geompy__doc__,			// m_doc
	-1,						// m_size
	geompy_methods,			// m_methods
	NULL, 					// m_slots
	NULL, 					// m_traverse: 
	NULL, 					// m_clear
	NULL  					// m_free
};

PyMODINIT_FUNC
PyInit__geompy(void) {
	PyObject* module = PyModule_Create(&geompy_module);

	if (PyType_Ready(&PyPolygon_Type) < 0) {
		Py_XDECREF(module);
		return NULL;
	}

	Py_INCREF(&PyPolygon_Type);
	PyModule_AddObject(module, PyPolygon_Type.tp_name, (PyObject*)&PyPolygon_Type);

	return module;
}