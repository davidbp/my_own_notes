"""
In order to build the cythoned version of a function the following command can be used:
python3 buchaca_builder.py build_ext --inplace
This command should create a file:  compute.cpython-36m-darwin.so
"""

from distutils.core import setup
from Cython.Build import cythonize

setup(ext_modules = cythonize("compute.pyx"))
