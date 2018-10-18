# Project

This project implements a max binary heap in C. The implementation of the heap was done using a dynamic array. Each node of the heap has associated a heap key and a abstract item which can be any C data structure.

# Repository Structure

* ### doc
Contains the documentation of the project that was automatically generated from the source files using Doxygen. The documentation can be accessed through doc/html/index.html

* ### test
Contains the unit tests of the project. These unit tests were based on the CUnit test framework. 

* ### src
Contains the source files (*.c)

* ### inc
Contains the header files (*.h)

# Compilation

The project can be compiled using the provided CMakeLists file. You can compile the project using the following commands:

```bash
mkdir build && cd build
cmake -G "Unix Makefiles" ../
make
```

If you also want to compile the unit tests you can use the following commands:

```bash
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../
make
```
