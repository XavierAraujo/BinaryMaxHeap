project(BinaryHeapExample)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Define the directory of the source code
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE C_SOURCES "${SRC_DIR}/*.c")

# Static linking of binary max heap
set( BINARY_HEAP_LIB "BinaryHeap")
set( BINARY_HEAP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/" )
set( BINARY_HEAP_STATIC ${CMAKE_CURRENT_SOURCE_DIR}/../build/lib${BINARY_HEAP_LIB}.a )
add_library( ${BINARY_HEAP_LIB} STATIC IMPORTED )
set_property( TARGET ${BINARY_HEAP_LIB} PROPERTY IMPORTED_LOCATION ${BINARY_HEAP_STATIC} )


include_directories( ${BINARY_HEAP_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${C_SOURCES}
                            ${C_INCLUDES})


target_link_libraries(${PROJECT_NAME} ${BINARY_HEAP_LIB})
