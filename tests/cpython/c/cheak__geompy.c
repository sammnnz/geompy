#include <stdio.h>
#include <stdlib.h>

#include <Python.h>
#include <check.h>

#ifndef LIB_SITEPACKAGES_PATH
#	define LIB_SITEPACKAGES_PATH 
#endif
#ifndef PY_PLATBASE
#	define PY_PLATBASE 
#endif
#ifndef SRC_PATH
#	define SRC_PATH 
#endif
#ifndef TESTS_CPYTHON_PATH
#	define TESTS_CPYTHON_PATH 
#endif

#define _mkstr(s) #s
#define _pytest_testfunc_call(p, m, t) _mkstr(p/m::t)
#define _pytest_testmodule_call(p, m) _mkstr(p/m)
#define MKSTR(s) _mkstr(s)
#define PYTEST_TESTFUNC_CALL(m, t) _pytest_testfunc_call(TESTS_CPYTHON_PATH, m.py, t)
#define PYTEST_TESTMODULE_CALL(m) _pytest_testmodule_call(TESTS_CPYTHON_PATH, m.py)

PyObject *provider_fn;
PyObject *provider_mo;
wchar_t *program;
wchar_t *py_platbase;

#define START_PYTEST_MODULE(mo) START_TEST(mo)\
{\
	PyObject *args;\
	PyObject *commands;\
	PyObject *value;\
	\
	commands = PyList_New(3);\
	if (! commands)\
		ck_abort_msg("Error: Failed to create `list` object.");\
	PyList_SET_ITEM(commands, 0, PyUnicode_FromString("--verbose"));\
	PyList_SET_ITEM(commands, 1, PyUnicode_FromString("-x"));\
	PyList_SET_ITEM(commands, 2, PyUnicode_FromString(\
		PYTEST_TESTMODULE_CALL(mo)));\
	args = PyTuple_New(1);\
	if (! args)\
	{\
		Py_CLEAR(commands);\
		ck_abort_msg("Error: Failed to create `tuple` object.");\
	}\
	PyTuple_SET_ITEM(args, 0, commands);\
	value = PyObject_CallObject(provider_fn, args);\
	Py_CLEAR(args);\
	if (PyErr_Occurred())\
			PyErr_Print();\
	if (! value)\
	{\
		ck_abort_msg("Error: Failed to execute `provider` function.\n\
NOTE: May be problem with arguments.");\
	}\
	Py_CLEAR(value);\
}\
END_TEST

#define START_PYTEST_FUNC(mo, t) START_TEST(t)\
{\
	PyObject *args;\
	PyObject *commands;\
	PyObject *value;\
	\
	commands = PyList_New(3);\
	if (! commands)\
		ck_abort_msg("Error: Failed to create `list` object.");\
	PyList_SET_ITEM(commands, 0, PyUnicode_FromString("--verbose"));\
	PyList_SET_ITEM(commands, 1, PyUnicode_FromString("-x"));\
	PyList_SET_ITEM(commands, 2, PyUnicode_FromString(\
		PYTEST_TESTFUNC_CALL(mo, t)));\
	args = PyTuple_New(1);\
	if (! args)\
	{\
		Py_CLEAR(commands);\
		ck_abort_msg("Error: Failed to create `tuple` object.");\
	}\
	PyTuple_SET_ITEM(args, 0, commands);\
	value = PyObject_CallObject(provider_fn, args);\
	Py_CLEAR(args);\
	if (PyErr_Occurred())\
			PyErr_Print();\
	if (! value)\
	{\
		ck_abort_msg("Error: Failed to execute `provider` function.\n\
NOTE: May be problem with arguments.");\
	}\
	Py_CLEAR(value);\
}\
END_TEST

/* Fixtures API */

// https://stackoverflow.com/questions/78247260/how-to-set-the-python-executable-name-now-that-py-setprogramname-is-deprecate
static void setup_program(void)
{
	PyObject *path_list;
	PyObject *sys_path;
	wchar_t *str_tmp;
	
	/*
	 * TODO: use PyConfig API.
	 * See more details https://docs.python.org/3.10/c-api/sys.html?highlight=py_decodelocale#c.Py_DecodeLocale
	*/
	program = Py_DecodeLocale(__argv[0], NULL);
    if (! program) {
		ck_abort_msg("Error: Cannot decode __argv[0].");
    }

	py_platbase = Py_DecodeLocale(MKSTR(PY_PLATBASE), NULL);
	if (! py_platbase){
		PyMem_RawFree(program);
		ck_abort_msg("Error: Cannot decode %s.", MKSTR(PY_PLATBASE));
	}

	Py_SetProgramName(program);
	Py_SetPythonHome(py_platbase);
    Py_Initialize();
	sys_path = PySys_GetObject("path");
	PyList_Insert(sys_path, 0, PyUnicode_FromString(MKSTR(LIB_SITEPACKAGES_PATH)));
	PyList_Insert(sys_path, 0, PyUnicode_FromString(MKSTR(SRC_PATH)));
	PyList_Insert(sys_path, 0, PyUnicode_FromString(MKSTR(TESTS_CPYTHON_PATH)));
    path_list = PyUnicode_Join(PyUnicode_FromWideChar(L"\n", -1), sys_path);
	str_tmp = PyUnicode_AsWideCharString(path_list, NULL);
	Py_XDECREF(path_list);
	if (str_tmp != NULL)
	{
		printf("sys.path:\n%ls\n", str_tmp);
		PyMem_Free(str_tmp);
	}
}

static void teardown_program(void)
{
	PyMem_RawFree(program);
	PyMem_RawFree(py_platbase);
	if (Py_FinalizeEx() < 0)
		ck_abort_msg("Warning: Python finalizaton is failed.");
}

static void import_provider(void)
{
	provider_mo = PyImport_Import(PyUnicode_FromString("provider"));
	if (! provider_mo)
	{
		if (PyErr_Occurred())
			PyErr_Print();
		
		teardown_program();
		ck_abort_msg("Error: Module `provider` is not exists.");
	}

	provider_fn = PyObject_GetAttrString(provider_mo, "provider");
	if (! (provider_fn && PyCallable_Check(provider_fn)))
	{
		if (PyErr_Occurred())
			PyErr_Print();

		Py_CLEAR(provider_mo);
		teardown_program();
		ck_abort_msg("Error: Function `provider` is not exists.");
	}
}

static void clear_provider(void)
{
	Py_CLEAR(provider_fn);
	Py_CLEAR(provider_mo);
}

/* Unittests */

START_PYTEST_MODULE(test__geompy)
// START_PYTEST_FUNC(test__geompy, test_polygon_is_inner_point_false_return)

Suite *_geompy_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("_geompy");
    tc_core = tcase_create("Core");
	// https://libcheck.github.io/check/doc/check_html/check_4.html#Test-Fixture-Examples
	tcase_add_unchecked_fixture(tc_core, setup_program, teardown_program);
	tcase_add_unchecked_fixture(tc_core, import_provider, clear_provider);
	tcase_add_test(tc_core, test__geompy);
	// tcase_add_test(tc_core, test_polygon_is_inner_point_false_return);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char *argv[])
{
	int number_failed;
	Suite *s;
    SRunner *sr;

    s = _geompy_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE); // CK_SILENT
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
