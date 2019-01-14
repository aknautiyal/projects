from distutils.core import setup, Extension
setup(name = 'calcModule', version = '1.0',  \
   ext_modules = [Extension('calcModule', ['calcmodule.c'])])
