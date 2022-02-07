minilsap
========

A Python module to solve the linear sum assignment problem (LSAP) efficiently.
Extracted from SciPy, without significant modifications.

This module is useful in cases when you need an efficient LSAP solver but you
do not want to depend on the full SciPy library.

Currently, the module depends on NumPy for array management. This may be
relaxed in the future if Python's stable API gets extended with functions to
manage Python buffer objects.

License
-------

The code in this repository is licensed under the 3-clause BSD license, except
for files including a different license header.

The LSAP solver copied from SciPy is also licensed under the 3-clause BSD
license.
