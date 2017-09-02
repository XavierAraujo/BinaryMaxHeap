project(BinaryHeap)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Define the directory of the source code and of the headers 
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../inc")
set(TEST_DIR ".")

FILE(GLOB_RECURSE MY_C_SOURCES "${SRC_DIR}/binary_heap.c")
FILE(GLOB_RECURSE MY_C_INCLUDES "${INC_DIR}/binary_heap.h")
FILE(GLOB_RECURSE MY_C_TEST_SOURCES "${TEST_DIR}/test_binary_heap.c")

include_directories( ${INC_DIR})


enable_testing()
add_executable(BinaryHeap_Test ${MY_C_SOURCES}
                               ${MY_C_INCLUDES}
                               ${MY_C_TEST_SOURCES})


target_link_libraries(BinaryHeap_Test "-lcunit")

add_test(BinaryHeap_Test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BinaryHeap_Test)

