
#include <stdlib.h>
#include <stdbool.h>

#include "binary_heap.h"

//
// Static functions declaration
//

static int binary_heap_reorder_after_push(BinaryHeap* bHeap);
static int binary_heap_reorder_after_pop(BinaryHeap* bHeap);
static bool binary_heap_has_childs(BinaryHeap* bHeap, int nodeIndex);
static bool binary_heap_is_parent_key_lower_than_child(BinaryHeap* bHeap, int parentIndex);
static int binary_heap_get_highest_key_child_index(BinaryHeap* bHeap, int parentIndex);
static int binary_heap_swap(BinaryHeap* bHeap, int index1, int index2);

//
// Header functions implementation
//

BinaryHeap* binary_heap_create(BinaryHeapCollector collector)
{
    BinaryHeap *heap = (BinaryHeap*) malloc(sizeof(BinaryHeap));
    heap->nodes = NULL;
    heap->collect = collector;
    heap->size = 0;
    return heap;
}

void binary_heap_destroy(BinaryHeap** bHeap)
{
    if((*bHeap) == NULL) {
        return;
    }

    if ((*bHeap)->collect != NULL) {
        for (int i=0; i < (*bHeap)->size; i++) {
            (*bHeap)->collect((*bHeap)->nodes[i].item);
        }
    }

    free((*bHeap)->nodes);
    free((*bHeap));
    (*bHeap) = NULL;
}

int binary_heap_push(BinaryHeap** bHeap, HeapNode node)
{
    // Protection against invalid heaps
    if((*bHeap) == NULL) {
        return -1;
    }

    // Reallocate the required memory
    int heapSize = (*bHeap)->size + 1;
    HeapNode* tmp = (HeapNode*) realloc((*bHeap)->nodes, heapSize*sizeof(HeapNode));
    if(!tmp) {
        return -1;
    }

    // In case of a successfull realocation update the heap size and reorder it to guarantee that the heap property is maintained
    (*bHeap)->nodes = tmp;
    (*bHeap)->size = heapSize;
    (*bHeap)->nodes[heapSize-1] = node;
    binary_heap_reorder_after_push(*bHeap);

    return 0;
}

HeapNode binary_heap_pop(BinaryHeap** bHeap)
{
    HeapNode node;

    // Protection against invalid heaps
    if((*bHeap) == NULL || (*bHeap)->size <= 0) {
        node.key = -1;
        return node;
    }

    node = (*bHeap)->nodes[0];
    // swap between the retrieved node and the last node must be done before memory reallocation
    binary_heap_swap((*bHeap), 0, (*bHeap)->size - 1);
    int heapSize = --((*bHeap)->size);
    (*bHeap)->nodes = (HeapNode*) realloc((*bHeap)->nodes, heapSize*sizeof(HeapNode));
    // reorder is needed after the swap
    binary_heap_reorder_after_pop((*bHeap));
    return node;
}

HeapNode* binary_heap_peek(BinaryHeap* bHeap)
{
    if(bHeap == NULL || bHeap->size == 0) {
      return NULL;
    }

    return &bHeap->nodes[0];
}

int binary_heap_get_size(BinaryHeap* bHeap)
{
    if (bHeap == NULL) {
        return -1;
    }

    return bHeap->size;
}

//
// Static functions implementation
//

// Reorganizes the binary heap after a new element being pushed. Returns 0 in case of success and -1 otherwise.
static int binary_heap_reorder_after_push(BinaryHeap* bHeap)
{
    // If the size is 0 or 1 no reorder is required
    if(bHeap == NULL || bHeap->size <= 1) {
        return -1;
    }

    // get the index of the element that was pushed (last element of the array)
    int pushedNodeIndex = bHeap->size - 1;

    while(true)
    {
        int parentIndex = (pushedNodeIndex-1)/2; // get the index of the parent of the pushed node

        // If the pushed node is on the top if the heap then the organization is concluded
        if (pushedNodeIndex == 0) {
            break;
        }

        // If the key of the pushed node is lower than the key of its parent the heap is already organized
        if(bHeap->nodes[pushedNodeIndex].key <= bHeap->nodes[parentIndex].key) {
            break;
        }

        // Otherwise we have to swap them and continue the analyzis
        binary_heap_swap(bHeap, pushedNodeIndex, parentIndex);
        pushedNodeIndex = parentIndex;
    }

    return 0;
}

// Reorganizes the binary heap after a element being popped. Returns 0 in case of success and -1 otherwise.
static int binary_heap_reorder_after_pop(BinaryHeap* bHeap)
{
    // If the size is 0 or 1 no reorder is required
    if(bHeap == NULL || bHeap->size <= 1) {
        return -1;
    }

    // get the index of the element that was swapped with the one that was popped (first element of the array)
    int swappedNodeIndex = 0;

    while(true)
    {
        // If the swapped node has no childs the heap is already organized.
        if (! binary_heap_has_childs(bHeap, swappedNodeIndex)) {
            break;
        }

        // If the key of the swapped node is higher than the key of its childs the heap is already organized
        if ( ! binary_heap_is_parent_key_lower_than_child(bHeap, swappedNodeIndex)) {
            break;
        }

        // Otherwise we have to swap the node with the child with the highest key and continue the analyzis
        int childIndex = binary_heap_get_highest_key_child_index(bHeap, swappedNodeIndex);
        binary_heap_swap(bHeap, swappedNodeIndex, childIndex);
        swappedNodeIndex = childIndex;
    }

    return 0;
}

// Analyzes if a given node has child nodes. Returns true if the node has at least one child and false otherwise.
static bool binary_heap_has_childs(BinaryHeap* bHeap, int nodeIndex)
{
    if(bHeap == NULL || bHeap->size <= 1) {
        return false;
    }

    // Get the indexes of the childs of the node
    int child1Index = 2*nodeIndex + 1;
    int child2Index = 2*nodeIndex + 2;

    // If those indexes exist on the array then the node has childs
    if ((child1Index > 0 && child1Index < bHeap->size) ||
         (child2Index > 0 && child2Index < bHeap->size)) {
        return true;
    }

    return false;
}

// Analyzes if the childs of a given node have a higher heap key.
// Returns true if one of the childs of the indicated parent has a higher key than the parent, and false otherwise.
static bool binary_heap_is_parent_key_lower_than_child(BinaryHeap* bHeap, int parentIndex)
{
    if(bHeap == NULL) {
        return false;
    }

    // Get the indexes of the childs of the node
    int child1Index = 2*parentIndex + 1;
    int child2Index = 2*parentIndex + 2;

    // Compare the key of the node with the key of its first child
    if (child1Index > 0 && child1Index < bHeap->size)
    {
        if(bHeap->nodes[parentIndex].key < bHeap->nodes[child1Index].key) {
            return true;
        }
    }

    // Compare the key of the node with the key of its second child
    if (child2Index > 0 && child2Index < bHeap->size)
    {
        if(bHeap->nodes[parentIndex].key < bHeap->nodes[child2Index].key) {
            return true;
        }
    }

    return false;
}

// Analyzes the childs of a parent node and it returns the index of the one with the hightest key.
// Returns the index of the child containing the highest key value.
static int binary_heap_get_highest_key_child_index(BinaryHeap* bHeap, int parentIndex)
{
    if(bHeap == NULL) {
        return -1;
    }

    // Get the indexes of the childs of the node
    int child1Index = 2*parentIndex + 1;
    int child2Index = 2*parentIndex + 2;

    int keyChild1 = -1;
    int keyChild2 = -1;

    // Get the key of the first child of the node
    if (child1Index > 0 && child1Index < bHeap->size)
        keyChild1 = bHeap->nodes[child1Index].key;

    // Get the key of the second child of the node
    if (child2Index > 0 && child2Index < bHeap->size)
        keyChild2 = bHeap->nodes[child2Index].key;

    return ((keyChild1 > keyChild2) ? child1Index: child2Index);
}

// Swaps two elements from the binary heap. Note that the index of the first element is 0.
// Returns 0 in case of success and -1 otherwise.
static int binary_heap_swap(BinaryHeap* bHeap, int index1, int index2)
{
    if( bHeap == NULL || index1 < 0 || index2 < 0 ||
        index1 >= bHeap->size || index2 >= bHeap->size) {
        return -1;
    }

    // If the indexes are equal no swap is needed
    if( index1 == index2) {
        return 0;
    }

    HeapNode auxNode;
    auxNode = bHeap->nodes[index1];
    bHeap->nodes[index1] = bHeap->nodes[index2];
    bHeap->nodes[index2] = auxNode;
    return 0;
}
