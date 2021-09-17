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

/* char *list[], int size*/
static PyObject *method_bubblesort(PyObject *self, PyObject *args);

/*int main()
{
    char *l1[MAX_LENGTH] = {"ab", "abb", "aba", "dce", "dca", "dax", "dra", "cag", "x"};
    printf("Print unsorted list:\n");
    for (int iii = 0; iii < 9; iii++) {
        printf("%s ", l1[iii]);
    }
    printf("\n");
    bubblesort(l1, 9);
    printf("Print sorted list:\n");
    for (int iii = 0; iii < 9; iii++) {
        printf("%s ", l1[iii]);
    }
    printf("\n");
    return 0;
}*/

static PyObject *method_bubblesort(PyObject *self, PyObject *args)
{
    PyObject *list;
    PyObject *item;

    if (!PyArg_ParseTuple(args, "O", &list))
        return NULL;


    Py_ssize_t length = PyList_Size(list);
    const char *clist[length];

    for (Py_ssize_t iii = 0; iii < length; iii++) {
        item = PyList_GetItem(list, iii);
        clist[iii] = PyUnicode_AsUTF8AndSize(item, NULL);
    }

    const char *tmp = "";
    Py_ssize_t size = length;
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

    for (Py_ssize_t iii = 0; iii < length; iii++) {
        item = PyUnicode_FromString(clist[iii]);
        PyList_SetItem(list, iii, item);
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef SortingMethods[] = {
    {"bubblesort", method_bubblesort, METH_VARARGS, "Bubblesort algorithm"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef sortingmodule = {
    PyModuleDef_HEAD_INIT,
    "sorting",
    NULL,
    -1,
    SortingMethods
};

PyMODINIT_FUNC PyInit_sorting(void) {
    return PyModule_Create(&sortingmodule);
}