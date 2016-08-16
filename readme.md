# python-MIL-STD-1553B
Драйвер mil-std-1553B-совместимых плат компании ЭЛКУС, изменённый для сборки с помощью [swig](http://www.swig.org) под [python](http://www.python.org).

## Изменения в оригинальном драйвере
* убраны вложенные структуры
* добавлены промежуточные структуры и объединения (union)

## Необходимые для сборки инструменты
* swig (на момент написания 3.0.10)
* python
* vs2015 / gcc

Необходимо чтобы пути ко всем исполняемым файлам (swig, gcc, python) были прописаны в PATH операционной системы (windows).

## Сборка
```
python -m pip install --upgrade setuptools wheel
python setup.py bdist_wheel
```

В репозитории находятся собранные бинарные версии драйвера для:
* Linux 64, Python 3.4, версия драйвера 4.06
* Windows 32, Python 3.3, версия драйвера 4.08
* Windows 32, Python 3.4, версия драйвера 4.08

Wheels:
* Linux 64, Python 3.5, 4.06
* Windows 64, Python 3.5, 4.08

## CFFI (экспериментально, только linux)
[CFFI](https://cffi.readthedocs.io/en/latest/) — альтернатива swig. Может использоваться в двух режимах:
* api: модуль компилируется си-компилятором и привязан к версии python (как в случае со swig).
* abi: модуль компилируется в shared library и не привязан к версии python.

В данный момент cffi (1.7.0) не поддерживает условную компиляцию посредством препроцессора, поэтому необходимо «прогнать» заголовочный файл `ltmk.h` с помощью `gcc`:
```
gcc -E ltmk.h > _ltmk.h
```
### api mode
build.py:
```python
from cffi import FFI


ffibuilder = FFI()
with open("ltmk.c") as fin:

    ffibuilder.set_source("_ltmk", fin.read())

with open("_ltmk.h") as fin:

    ffibuilder.cdef(fin.read())

ffibuilder.compile(verbose=True)
```
```shell
$ python build.py
```
На выходе получится `_ltmk.cpython-35m-x86_64-linux-gnu.so`. В python это импортируется следующим образом:
```python
from _ltmk import ffi
from _ltmk import lib as ltmk
...
```
### abi mode
Сначала необходимо сделать shared library из си-библиотеки:
```shell
$ gcc -shared -o libltmk.so -fPIC ltmk.c
```
В python это импортируется следующим образом:
```python
from cffi import FFI


ffi = FFI()
with open("_ltmk.h") as fin:

    ffi.cdef(fin.read())

ltmk = ffi.dlopen("./libltmk.so")
...
```
### Пример использования
В обоих режимах вы получаете `ffi` и `ltmk`. Первый для создания объектов (структур), второй — для вызова функций.
```python
ltmk.TmkOpen()
ltmk.tmkconfig(0)
ltmk.tmkselect(0)

e = ffi.new("TTmkEventData *")
ltmk.tmkgetevd(e)
```
