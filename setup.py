from distutils.core import setup, Extension

if __name__ == '__main__':
    setup(ext_modules=[Extension('_geompy', ['src/_geompy/objects/polygonobject.c',
                                            'src/_geompy/resources/rand.c',
                                            'src/_geompy/_geompy.c'])]
          )
