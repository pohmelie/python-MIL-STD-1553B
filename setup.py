import sys
from setuptools import setup, Extension


if sys.platform == "win32":

    version = "4.6"
    files = [
        "WDMTMKv2.i",
        "WDMTMKv2.cpp",
    ]
    swig_opts = [
        "-py3",
        "-c++",
        "-module",
        "milstd1553b"
    ]

elif sys.platform == "linux":

    version = "4.8"
    files = [
        "ltmk.i",
        "ltmk.c",
    ]
    swig_opts = [
        "-py3",
        "-module",
        "milstd1553b"
    ]

else:

    raise Exception(str.format("Unsupported platform {}", sys.platform))

setup(
    name="milstd1553b",
    version=version,
    py_modules=["milstd1553b"],
    ext_modules=[
        Extension(
            "_milstd1553b",
            files,
            swig_opts=swig_opts,
        )
    ],
)
