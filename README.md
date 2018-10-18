# Project

This project implements a max binary heap in C. The implementation of the heap was done using a dynamic array. Each node of the heap has associated a heap key and a abstract item which can be any C data structure.


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
