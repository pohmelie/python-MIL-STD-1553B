from cffi import FFI


ffi = FFI()
with open("_ltmk.h") as fin:

    ffi.cdef(fin.read())

ltmk = ffi.dlopen("./libltmk.so")

ltmk.TmkOpen()
ltmk.tmkconfig(0)
ltmk.tmkselect(0)

e = ffi.new("TTmkEventData *")
ltmk.tmkgetevd(e)
