python.install_sources(
  [
    'geompy/__init__.py',
    'geompy/_typing.py',
    'geompy/geompy.py',
    'geompy/geompy.pyi',
  ],
  pure : false,
  subdir : 'src/geompy'
)

extension = python.extension_module(
  '_geompy',
  sources: [
    '_geompy/_geompy.c',
    '_geompy/objects/polygonobject.c'
    ],
  dependencies: [py_dep],
  include_directories: ['_geompy/include'],
  install: true,
  subdir : 'src/_geompy'
)