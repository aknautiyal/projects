#include <Python.h>


int sqr(int a)
{
	return a * a;
}

int add(int a, int b)
{
	return a+b;
}

static PyObject *calc_add(PyObject *self, PyObject *args)
{
	int a,b;
	int result;

	if (!PyArg_ParseTuple(args, "ii", &a, &b))
		return NULL;
	result = add(a, b);
	return Py_BuildValue("i", result);
}
	
static PyObject *calc_sqr(PyObject *self, PyObject *args)
{
	int a;
	int result;

	if (!PyArg_ParseTuple(args, "i", &a))
		return NULL;
	result = sqr(a);
	return Py_BuildValue("i", result);
}

static PyMethodDef CalcModuleMethods[] = {
	{"calc_sqr", calc_sqr, METH_VARARGS, "Squares a number"},
	{"calc_add", calc_add, METH_VARARGS, "Add two numbers"},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initcalcModule(void)
{
    PyObject *m;

    m = Py_InitModule3("calcModule", CalcModuleMethods, "Calculator");
    if (m == NULL)
        return;
}

void main(int argc, char *argv[])
{
	Py_SetProgramName(argv[0]);
	Py_Initialize();
	initcalcModule();
}
