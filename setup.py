"""
setup.py
"""
import os

from setuptools import setup, Extension

# https://stackoverflow.com/questions/18085571/pip-install-error-setup-script-specifies-an-absolute-path
current_dir = "./"
source_dir = os.path.join(current_dir, "src", "_geompy")
include_dir = os.path.join(source_dir, "include")

if __name__ == '__main__':
    setup(ext_modules=[Extension(name='_geompy',
                                 sources=[os.path.join(source_dir, '_geompy.c'),
                                          os.path.join(source_dir, 'objects', 'polygonobject.c')],
                                 include_dirs=[include_dir],
                                 extra_compile_args=['--std=c99'],
                                 language="c"
                                 )
                       ]
          )
