from cffi import FFI


ffi = FFI()
with open("_ltmk.h") as fin:

    ffi.cdef(fin.read())

ltmk = ffi.dlopen("./libltmk.so")

assert ltmk.TmkOpen() == 0
assert ltmk.tmkconfig(0) == 0
assert ltmk.tmkselect(0) == 0

e = ffi.new("TTmkEventData *")
ltmk.tmkgetevd(e)
print("ok")
