#include "binary_heap.h"

binaryHeap* create()
{
    binaryHeap *heap = (binaryHeap*) malloc(sizeof(binaryHeap));
    heap->nodes = NULL;
    heap->size = 0;
    return heap;
}

int size(binaryHeap* bHeap)
{
    if (bHeap == NULL)
        return -1;

    return bHeap->size;
}

int push(binaryHeap** bHeap, heapNode node)
{
    // Try to reallocate the required memory
    int heapSize = (*bHeap)->size + 1;
    heapNode* tmp = (heapNode*) realloc((*bHeap)->nodes, heapSize*sizeof(heapNode));
    if(! tmp)
        return -1;

    // Update and reorder the heap in case of a successfull realocation
    (*bHeap)->nodes = tmp;
    (*bHeap)->size = heapSize;
    (*bHeap)->nodes[heapSize-1] = node;
    reorderAfterPush((*bHeap));

    return 0;
}

static void reorderAfterPush(binaryHeap* bHeap)
{
    // If the size is 0 or 1 no reorder is required
    if(bHeap == NULL || bHeap->size <= 1)
        return;

    int currIndex = bHeap->size - 1;
    while(true)
    {
        int parent = (currIndex-1)/2; // get the index of the parent of the current node

        // If key of the node in analyzis is lower than the key
        // of its parent the heap is organized.
        // Otherwise we have to swap them
        if(bHeap->nodes[currIndex].key <= bHeap->nodes[parent].key
            || currIndex == 0)
            break;

        swap(bHeap, currIndex, parent);
        currIndex = parent;
    }
}

static void reorderAfterPop(binaryHeap* bHeap)
{
    // If the size is 0 or 1 no reorder is required
    if(bHeap == NULL || bHeap->size <= 1)
        return;

    int currIndex = 0;
    while(true)
    {
        if (! hasChilds(bHeap, currIndex))
            break;

        if ( ! isParentKeyLowerThanChild(bHeap, currIndex))
            break;


        int childIndex = getIndexOfHighestKeyChild(bHeap, currIndex);
        swap(bHeap, currIndex, childIndex);
        currIndex = childIndex;
    }
}

static bool hasChilds(binaryHeap* bHeap, int nodeIndex)
{
    int child1Index = 2*nodeIndex + 1;
    int child2Index = 2*nodeIndex + 2;

    if ((child1Index > 0 && child1Index < bHeap->size) ||
         (child2Index > 0 && child2Index < bHeap->size))
        return true;

    return false;
}

static bool isParentKeyLowerThanChild(binaryHeap* bHeap, int parentIndex)
{
    int child1Index = 2*parentIndex + 1;
    int child2Index = 2*parentIndex + 2;

    if (child1Index > 0 && child1Index < bHeap->size)
    {
        if(bHeap->nodes[parentIndex].key < bHeap->nodes[child1Index].key)
            return true;
    }

    if (child2Index > 0 && child2Index < bHeap->size)
    {
        if(bHeap->nodes[parentIndex].key < bHeap->nodes[child2Index].key)
            return true;
    }

    return false;
}

static int getIndexOfHighestKeyChild(binaryHeap* bHeap, int parentIndex)
{
    int child1Index = 2*parentIndex + 1;
    int child2Index = 2*parentIndex + 2;

    int keyChild1 = -1;
    int keyChild2 = -1;

    if (child1Index > 0 && child1Index < bHeap->size)
        keyChild1 = bHeap->nodes[child1Index].key;

    if (child2Index > 0 && child2Index < bHeap->size)
        keyChild2 = bHeap->nodes[child2Index].key;

    return ((keyChild1 > keyChild2) ? child1Index: child2Index);
}


static void swap(binaryHeap* bHeap, int index1, int index2)
{
    if( index1 < 0 || index2 < 0 ||
        index1 >= bHeap->size || index2 >= bHeap->size ||
        index1 == index2)
        return;

    heapNode auxNode;
    auxNode = bHeap->nodes[index1];
    bHeap->nodes[index1] = bHeap->nodes[index2];
    bHeap->nodes[index2] = auxNode;
}

heapNode pop(binaryHeap** bHeap)
{
    //if(bHeap == NULL || bHeap->size <= 0)
    //    return

    heapNode node = (*bHeap)->nodes[0];
    swap((*bHeap), 0, (*bHeap)->size - 1);
    int heapSize = --((*bHeap)->size);
    (*bHeap)->nodes = (heapNode*) realloc((*bHeap)->nodes, heapSize*sizeof(heapNode));
    reorderAfterPop((*bHeap));
    return node;
}

heapNode* peek(binaryHeap* bHeap)
{
    if(bHeap == NULL || bHeap->size == 0)
      return NULL ;

    return &bHeap->nodes[0];
}


void destroy(binaryHeap** bHeap)
{
    free((*bHeap)->nodes);
    free((*bHeap));
    (*bHeap) = NULL;
}

