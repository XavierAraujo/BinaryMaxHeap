#include <stdio.h>
#include <string.h>

#include "binary_heap.h"

int main(int argc, char** argv[])
{
    heapNode node;
    binaryHeap* myHeap = create();
    print(myHeap);

    node.key = 100;
    strcpy(node.name, "nodeA");
    push(&myHeap, node);
    print(myHeap);

    node.key = 90;
    strcpy(node.name, "nodeB");
    push(&myHeap, node);
    print(myHeap);

    node.key = 80;
    strcpy(node.name, "nodeC");
    push(&myHeap, node);
    print(myHeap);

    node.key = 95;
    strcpy(node.name, "nodeD");
    push(&myHeap, node);
    print(myHeap);

    heapNode poppedNode = pop(&myHeap);
    print(myHeap);

    printf("\n");
    printf("poppedNode -> key:%i, name:%s\n", poppedNode.key, poppedNode.name);

    destroy(&myHeap);
    myHeap = NULL;
    print(myHeap);

    return 0;
}


