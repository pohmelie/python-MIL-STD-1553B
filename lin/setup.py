import distutils
from distutils.core import setup, Extension


setup(
    name = "MIL-STD-1553B",
    version = "4.06",
    ext_modules = [Extension(
        "_ltmk",
        ["ltmk.i","ltmk.c"],
        swig_opts=["-py3", "-module", "ltmk"],
    )]
)
