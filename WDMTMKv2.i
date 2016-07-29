%module WDMTNKv2

%typemap(in) HANDLE {
    $1 = (void *)(PyInt_AsLong($input));
}

%typemap(out) HANDLE {
    $result = PyInt_FromLong((int)($1));
}

%{
#include "WDMTMKv2.h"
%}

%include <windows.i>

%include <carrays.i>
%array_class(unsigned short int, WordBuffer);

%include "WDMTMKv2.h"
