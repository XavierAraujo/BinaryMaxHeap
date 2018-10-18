project(BinaryHeap)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Define the directory of the source code and headers
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE C_SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE C_INCLUDES "${INC_DIR}/*.h")

include_directories( ${INC_DIR})

if(CMAKE_BUILD_TYPE MATCHES Debug) # Compile for testing

    set(TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/src")
    file(GLOB_RECURSE C_TEST_SOURCES "${TEST_SRC_DIR}/*.c")

    # Setup CUnit framework
    find_library(C_UNIT NAMES cunit libcunit cunitlib)
    if(NOT C_UNIT)
        message(FATAL_ERROR "CUnit library not found. This library is required to run the unit tests")
    endif()

    message(STATUS "Found CUnit library at ${C_UNIT}")


    # test binary that executes the unit tests
    set(BINARY_HEAP_TEST_EXECUTABLE "TestBinaryHeap")
    add_executable( ${BINARY_HEAP_TEST_EXECUTABLE}
        ${C_SOURCES}
        ${C_TEST_SOURCES}
        ${C_INCLUDES}
        ${CUNIT_INCLUDE_DIRS} )

endif()


add_library(${PROJECT_NAME} ${C_SOURCES}
                            ${C_INCLUDES})


target_link_libraries(${PROJECT_NAME})
