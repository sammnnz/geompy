"""
setup.py
"""
# import os

from distutils.core import setup, Extension

if __name__ == '__main__':
    # rootdir = os.path.normpath(os.path.join(__file__, os.pardir))
    setup(ext_modules=[Extension(name='_geompy',
                                 sources=[
                                     # os.path.join(rootdir, 'src/_geompy/objects/polygonobject.c'),
                                     # os.path.join(rootdir, 'src/_geompy/resources/rand.c'),
                                     # os.path.join(rootdir, 'src/_geompy/_geompy.c'),
                                     'src/_geompy/objects/polygonobject.c',
                                     'src/_geompy/resources/rand.c',
                                     'src/_geompy/_geompy.c'
                                 ],
                                 include_dirs=['src/_geompy',
                                               #  'src/_geompy/clinic',
                                               #  'src/_geompy/cpython',
                                               #  'src/_geompy/includes',
                                               #  'src/_geompy/includes/cpython',
                                               #  'src/_geompy/objects/clinic'
                                               ],
                                 extra_compile_args=['-std=c99']
                                 )
                       ]
          )
