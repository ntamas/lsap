/*
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided
   with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Original version of this source code is from SciPy 1.8.0, downloaded from
   https://github.com/scipy/scipy/blob/main/scipy/optimize/_lsap_module.c

   Slight modifications to the includes, code reformatting, Clang compiler
   fixes and renaming of the module were done by Tamas Nepusz <ntamas@gmail.com>
*/

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "numpy/arrayobject.h"
#include "numpy/ndarraytypes.h"
#include "rectangular_lsap.h"

static PyObject* solve(PyObject* self, PyObject* args)
{
    PyObject* a = NULL;
    PyObject* b = NULL;
    PyObject* result = NULL;
    PyObject* obj_cost = NULL;
    int maximize = 0;
    int ret;
    npy_intp num_rows, num_cols, dim;
    int64_t *pa, *pb;
    double* cost_matrix;

    if (!PyArg_ParseTuple(args, "Op", &obj_cost, &maximize))
        return NULL;

    PyArrayObject* obj_cont = (PyArrayObject*)PyArray_ContiguousFromAny(obj_cost, NPY_DOUBLE, 0, 0);
    if (!obj_cont) {
        return NULL;
    }

    if (PyArray_NDIM(obj_cont) == 0 || (PyArray_NDIM(obj_cont) == 1 && PyArray_DIM(obj_cont, 0) == 0)) {
        dim = 0;
        a = PyArray_SimpleNew(1, &dim, NPY_INT64);
        if (!a)
            goto cleanup;

        b = PyArray_SimpleNew(1, &dim, NPY_INT64);
        if (!b)
            goto cleanup;

        goto ok;
    }

    if (PyArray_NDIM(obj_cont) != 2) {
        PyErr_Format(PyExc_ValueError,
            "expected a matrix (2-D array), got a %d array",
            PyArray_NDIM(obj_cont));
        goto cleanup;
    }

    cost_matrix = (double*)PyArray_DATA(obj_cont);
    if (cost_matrix == NULL) {
        PyErr_SetString(PyExc_TypeError, "invalid cost matrix object");
        goto cleanup;
    }

    num_rows = PyArray_DIM(obj_cont, 0);
    num_cols = PyArray_DIM(obj_cont, 1);
    dim = num_rows < num_cols ? num_rows : num_cols;
    a = PyArray_SimpleNew(1, &dim, NPY_INT64);
    if (!a)
        goto cleanup;

    b = PyArray_SimpleNew(1, &dim, NPY_INT64);
    if (!b)
        goto cleanup;

    pa = (int64_t*)PyArray_DATA((PyArrayObject*)a);
    pb = (int64_t*)PyArray_DATA((PyArrayObject*)b);

    Py_BEGIN_ALLOW_THREADS;

    ret = solve_rectangular_linear_sum_assignment(
        num_rows, num_cols, cost_matrix, maximize, pa, pb);

    Py_END_ALLOW_THREADS;

    if (ret == RECTANGULAR_LSAP_INFEASIBLE) {
        PyErr_SetString(PyExc_ValueError, "cost matrix is infeasible");
        goto cleanup;
    } else if (ret == RECTANGULAR_LSAP_INVALID) {
        PyErr_SetString(PyExc_ValueError,
            "matrix contains invalid numeric entries");
        goto cleanup;
    }

ok:
    result = Py_BuildValue("OO", a, b);

cleanup:
    Py_XDECREF((PyObject*)obj_cont);
    Py_XDECREF(a);
    Py_XDECREF(b);
    return result;
}

static PyMethodDef lsap_module_methods[] = {
    { "solve", solve, METH_VARARGS, "Solves the rectangular linear sum assignment problem." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "minilsap._lsap",
    "Solves the rectangular linear sum assignment.",
    -1,
    lsap_module_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};

extern "C" PyObject* PyInit__lsap(void)
{
    PyObject* m;
    m = PyModule_Create(&moduledef);
    import_array();
    return m;
}
