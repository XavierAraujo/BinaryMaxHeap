# Project

This project implements a max binary heap in C. The implementation of the heap was done using a dynamic array. Each node of the heap has associated a heap key and a name.

# Repository Structure

* ### bin
Contains the binary file that resulted from the build procedure

* ### doc
Contains the documentation of the project that was automatically generated from the source files using Doxygen. The documentation can be accessed through doc/html/index.html

* ### test
Contains the unit tests of the project. These unit tests were based on the CUnit test framework. 

* ### src
Contains the source files (*.c)

* ### inc
Contains the header files (*.h)

# Compilation

The project can be compiled using the CMakeLists.txt file available. If you are using Linux you can use the scripts compile.sh and clean.sh.

# Tests
To run the test suite you will first need to install the CUnit library. After that you can use the CMakeLists.txt available on the test folder to build the test binary file. If you are using Linux you can use the script compile_tests.sh.
