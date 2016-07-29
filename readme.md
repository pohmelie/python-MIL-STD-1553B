#python-MIL-STD-1553B
Драйвер mil-std-1553B-совместимых плат компании ЭЛКУС, изменённый для сборки с помощью [swig](http://www.swig.org) под [python](http://www.python.org).

##Изменения в оригинальном драйвере
* убраны вложенные структуры
* добавлены промежуточные структуры и объединения (union)

##Необходимые для сборки инструменты
* swig (на момент написания 3.0.10)
* python
* vs2015 / gcc

Необходимо чтобы пути ко всем исполняемым файлам (swig, gcc, python) были прописаны в PATH операционной системы (windows).

##Сборка
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
