#include "binary_heap.h"

binaryHeap* create()
{
    binaryHeap *heap = (binaryHeap*) malloc(sizeof(binaryHeap));
    heap->nodes = NULL;
    heap->size = 0;
    return heap;
}

void destroy(binaryHeap** bHeap)
{
    free((*bHeap)->nodes);
    free((*bHeap));
    (*bHeap) = NULL;
}

int push(binaryHeap** bHeap, heapNode node)
{
    // Protection against invalid heaps
    if((*bHeap) == NULL || (*bHeap)->size < 0)
        return -1;

    // Reallocate the required memory
    int heapSize = (*bHeap)->size + 1;
    heapNode* tmp = (heapNode*) realloc((*bHeap)->nodes, heapSize*sizeof(heapNode));
    if(! tmp)
        return -1;

    // In case of a successfull realocation update the heap size and reorder it to guarantee that the heap property is maintained
    (*bHeap)->nodes = tmp;
    (*bHeap)->size = heapSize;
    (*bHeap)->nodes[heapSize-1] = node;
    reorderAfterPush(*bHeap);

    return 0;
}

heapNode pop(binaryHeap** bHeap)
{
    heapNode node;

    // Protection against invalid heaps
    if((*bHeap) == NULL || (*bHeap)->size <= 0)
    {
        node.key = -1;
        return node;
    }

    node = (*bHeap)->nodes[0];
    // swap between the retrieved node and the last node must be done before memory reallocation
    swap((*bHeap), 0, (*bHeap)->size - 1);
    int heapSize = --((*bHeap)->size);
    (*bHeap)->nodes = (heapNode*) realloc((*bHeap)->nodes, heapSize*sizeof(heapNode));
    // reorder is needed after the swap
    reorderAfterPop((*bHeap));
    return node;
}

heapNode* peek(binaryHeap* bHeap)
{
    if(bHeap == NULL || bHeap->size == 0)
      return NULL ;

    return &bHeap->nodes[0];
}

int size(binaryHeap* bHeap)
{
    if (bHeap == NULL)
        return -1;

    return bHeap->size;
}

static int reorderAfterPush(binaryHeap* bHeap)
{
    // If the size is 0 or 1 no reorder is required
    if(bHeap == NULL || bHeap->size <= 1)
        return -1;

    // get the index of the element that was pushed (last element of the array)
    int pushedNodeIndex = bHeap->size - 1;

    while(true)
    {
        int parentIndex = (pushedNodeIndex-1)/2; // get the index of the parent of the pushed node

        // If the pushed node is on the top if the heap then the organization is concluded
        if (pushedNodeIndex == 0)
            break;

        // If the key of the pushed node is lower than the key of its parent the heap is already organized
        if(bHeap->nodes[pushedNodeIndex].key <= bHeap->nodes[parentIndex].key)
            break;

        // Otherwise we have to swap them and continue the analyzis
        swap(bHeap, pushedNodeIndex, parentIndex);
        pushedNodeIndex = parentIndex;
    }

    return 0;
}

static int reorderAfterPop(binaryHeap* bHeap)
{
    // If the size is 0 or 1 no reorder is required
    if(bHeap == NULL || bHeap->size <= 1)
        return -1;

    // get the index of the element that was swapped with the one that was popped (first element of the array)
    int swappedNodeIndex = 0;

    while(true)
    {
        // If the swapped node has no childs the heap is already organized.
        if (! hasChilds(bHeap, swappedNodeIndex))
            break;

        // If the key of the swapped node is higher than the key of its childs the heap is already organized
        if ( ! isParentKeyLowerThanChild(bHeap, swappedNodeIndex))
            break;

        // Otherwise we have to swap the node with the child with the highest key and continue the analyzis
        int childIndex = getIndexOfHighestKeyChild(bHeap, swappedNodeIndex);
        swap(bHeap, swappedNodeIndex, childIndex);
        swappedNodeIndex = childIndex;
    }

    return 0;
}

static bool hasChilds(binaryHeap* bHeap, int nodeIndex)
{
    if(bHeap == NULL || bHeap->size <= 1)
        return false;

    // Get the indexes of the childs of the node
    int child1Index = 2*nodeIndex + 1;
    int child2Index = 2*nodeIndex + 2;

    // If those indexes exist on the array then the node has childs
    if ((child1Index > 0 && child1Index < bHeap->size) ||
         (child2Index > 0 && child2Index < bHeap->size))
        return true;

    return false;
}

static bool isParentKeyLowerThanChild(binaryHeap* bHeap, int parentIndex)
{
    if(bHeap == NULL)
        return false;

    // Get the indexes of the childs of the node
    int child1Index = 2*parentIndex + 1;
    int child2Index = 2*parentIndex + 2;

    // Compare the key of the node with the key of its first child
    if (child1Index > 0 && child1Index < bHeap->size)
    {
        if(bHeap->nodes[parentIndex].key < bHeap->nodes[child1Index].key)
            return true;
    }

    // Compare the key of the node with the key of its second child
    if (child2Index > 0 && child2Index < bHeap->size)
    {
        if(bHeap->nodes[parentIndex].key < bHeap->nodes[child2Index].key)
            return true;
    }

    return false;
}

static int getIndexOfHighestKeyChild(binaryHeap* bHeap, int parentIndex)
{
    if(bHeap == NULL)
        return -1;

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

static int swap(binaryHeap* bHeap, int index1, int index2)
{
    if( bHeap == NULL || index1 < 0 || index2 < 0 ||
        index1 >= bHeap->size || index2 >= bHeap->size)
        return -1;

    // If the indexes are equal no swap is needed
    if( index1 == index2)
        return 0;

    heapNode auxNode;
    auxNode = bHeap->nodes[index1];
    bHeap->nodes[index1] = bHeap->nodes[index2];
    bHeap->nodes[index2] = auxNode;
    return 0;
}
