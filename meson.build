project('geompy', 'c',
  version : '0.2.1a',
  meson_version : '>= 1.1',
  default_options : [
    'warning_level=3',
    'c_std=c99',
    'buildtype=debugoptimized',
    ]
)

cc = meson.get_compiler('c')

if cc.get_id() != 'gcc'
  error('GeomPy requires only GCC')
endif

python = import('python').find_installation(get_option('python'), pure: false)

if python.language_version().version_compare('< 3.7')
  error('Requires Python >= 3.7')
endif

py_dep = python.dependency()

if not cc.has_header('Python.h', dependencies: py_dep)
  error('Cannot compile `Python.h`. Perhaps you need to install python-dev|python-devel')
endif

subdir('src')