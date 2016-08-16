from cffi import FFI


ffibuilder = FFI()
with open("ltmk.c") as fin:

    ffibuilder.set_source("_ltmk", fin.read())

with open("_ltmk.h") as fin:

    ffibuilder.cdef(fin.read())

ffibuilder.compile(verbose=True)
