/*
Author : Darjengar
Date : 09/17/2021
GPL License
*/

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 15

static PyObject *method_bubblesort(PyObject *self, PyObject *args);
void bubblesort(PyObject *list);
void cpy2cstrlist(PyObject *list, const char *clist[]);
void cpy2strlist(const char *clist[], PyObject *list);
void sort_wrapper()

static PyObject *method_bubblesort(PyObject *self, PyObject *args)
{
    PyObject *list;

    if (!PyArg_ParseTuple(args, "O", &list))
        return NULL;

    Py_ssize_t size = PyList_Size(list);
    const char *clist[size];

    cpy2cstrlist(list, clist, size);
    bubblesort(list, size);
    cpy2strlist(clist, list, size);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef SortingMethods[] = {
    {"bubblesort", method_bubblesort, METH_VARARGS,
     "Bubblesort algorithm"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef sortingmodule = {
    PyModuleDef_HEAD_INIT,
    "sorting",
    NULL,
    -1,
    SortingMethods
};

PyMODINIT_FUNC PyInit_sorting(void)
{
    return PyModule_Create(&sortingmodule);
}

void bubblesort(PyObject *list, Py_ssize_t size)
{
    const char *tmp = "";
    while (size > 1) {
        for (Py_ssize_t iii = 0; iii < size-1; iii++) {
            if (strcmp(clist[iii], clist[iii+1]) > 0) {
                tmp = clist[iii];
                clist[iii] = clist[iii+1];
                clist[iii+1] = tmp;
            }
        }
        size--;
    }
}

void cpy2cstrlist(PyObject *list, const char *clist[], Py_ssize_t size)
{
    PyObject *item;
    for (Py_ssize_t iii = 0; iii < size; iii++) {
        item = PyList_GetItem(list, iii);
        clist[iii] = PyUnicode_AsUTF8(item);
    }
}

void cpy2strlist(const char *clist[], PyObject *list, Py_ssize_t size)
{
    PyObject *item;
    for (Py_ssize_t iii = 0; iii < size; iii++) {
        item = PyUnicode_FromString(clist[iii]);
        PyList_SetItem(list, iii, item);
    }
}

void sort