"""
setup.py
"""
from distutils.core import setup, Extension

if __name__ == '__main__':
    setup(ext_modules=[Extension(name='_geompy',
                                 sources=['src/_geompy/_geompy.c',
                                          'src/_geompy/objects/polygonobject.c'],
                                 include_dirs=['src/_geompy/include'],
                                 extra_compile_args=['--std=c99', '--coverage'],
                                 language="c"
                                 )
                       ]
          )
