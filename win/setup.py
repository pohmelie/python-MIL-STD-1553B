import distutils
from distutils.core import setup, Extension

setup(
    name = "MIL-STD-1553B",
    version = "4.08",
    ext_modules = [Extension(
        "_WDMTMKv2",
        ["WDMTMKv2.i", "WDMTMKv2.cpp"],
        swig_opts=['-py3', '-c++', '-module','WDMTMKv2'],
    )]
)
