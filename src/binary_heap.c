#include "binary_heap.h"

binaryHeap* create()
{
    binaryHeap *heap;

    // Allocate space for the heap and set its size to 0
    heap = (binaryHeap*) malloc(sizeof(binaryHeap));
    heap->size = 0;
    return heap;
}

int size(binaryHeap* bHeap)
{
    return bHeap->size;
}
