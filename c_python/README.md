embedding C code in Python.

eg.

>> import calcModule
>> sum = calcModule.add(3,4)
>> print sum


where add() is a c function defined in a C library.

to build:
python setup.py build
sudo python setup.py install
sudo python setup.py sdist
