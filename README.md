# GeomPy
[![license](https://img.shields.io/badge/License-APACHE_2.0-blue.svg)](http://www.apache.org/licenses/)
![Tests-ubuntu](https://github.com/sammnnz/geompy/actions/workflows/tests-ub.yml/badge.svg)
![Tests-win](https://github.com/sammnnz/geompy/actions/workflows/tests-win.yml/badge.svg)
![Tests-mac](https://github.com/sammnnz/geompy/actions/workflows/tests-mac.yml/badge.svg)
[![codecov](https://codecov.io/gh/sammnnz/geompy/branch/main/graph/badge.svg?token=64XGVB6FSV)](https://codecov.io/gh/sammnnz/geompy)


Python/C API demo project for geometry calculations.

### Feature
Implemented `is_inner_point` method of `polygon` class.
This function determines location of given point relative a polygon.

### Install
pip install "git+https://github.com/sammnnz/geompy@v0.2.1"

### Usage
Using the `polygon.is_inner_point` function, you can determine where the `point` is located relative to the `polygon`: outside or inside.

### Compatibility
Tested on Python `3.7`, `3.8`, `3.9`, `3.10` on `Windows`, `Ubuntu` and `Mac` platforms.

### Example
You can see `1.py` file from example directory.

### Other
Coverage report calculate for C and Python code, then deploy to [codecov](https://codecov.io/gh/sammnnz/geompy).
