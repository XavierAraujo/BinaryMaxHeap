#include <stdio.h>
#include <string.h>

#include <CUnit/Basic.h>

#include "binary_heap.h"


// Useful method to construct and return a node with a given key and name
heapNode HeapNodeConstructor(int key, char* name)
{
    heapNode hNode;
    hNode.key = key;
    strcpy(hNode.name, name);
    return hNode;
}

void test_create_and_destroy(void)
{
  binaryHeap* bHeap = create();
  CU_ASSERT_PTR_NOT_NULL(bHeap);
  CU_ASSERT_PTR_NULL(bHeap->nodes);
  CU_ASSERT(bHeap->size == 0);
  destroy(&bHeap);
  CU_ASSERT_PTR_NULL(bHeap);
}

void test_heap_manipulation()
{
    heapNode* hNode = NULL;
    heapNode poppedNode;
    binaryHeap* bHeap = create();

    push(&bHeap, HeapNodeConstructor(100, "NodeA")); // 1
    push(&bHeap, HeapNodeConstructor(120, "NodeC")); // 2
    push(&bHeap, HeapNodeConstructor(90 , "NodeD")); // 3
    push(&bHeap, HeapNodeConstructor(95 , "NodeE")); // 4
    push(&bHeap, HeapNodeConstructor(110, "NodeF")); // 5
    push(&bHeap, HeapNodeConstructor(75 , "NodeG")); // 6
    push(&bHeap, HeapNodeConstructor(80 , "NodeH")); // 7
    push(&bHeap, HeapNodeConstructor(115, "NodeH")); // 8
    push(&bHeap, HeapNodeConstructor(113, "NodeI")); // 9
    push(&bHeap, HeapNodeConstructor(116, "NodeJ")); // 10
    push(&bHeap, HeapNodeConstructor(60 , "NodeL")); // 11
    push(&bHeap, HeapNodeConstructor(74 , "NodeM")); // 12
    push(&bHeap, HeapNodeConstructor(73 , "NodeN")); // 13
    push(&bHeap, HeapNodeConstructor(70 , "NodeO")); // 14
    push(&bHeap, HeapNodeConstructor(130, "NodeP")); // 15

    // Assert key/name after push procedures
    CU_ASSERT(size(bHeap) == 15);
    CU_ASSERT(bHeap->nodes[0].key == 130); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].name , "NodeP", strlen("NodeP"));
    CU_ASSERT(bHeap->nodes[1].key == 116); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[1].name , "NodeJ", strlen("NodeJ"));
    CU_ASSERT(bHeap->nodes[2].key == 120); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[2].name , "NodeC", strlen("NodeC"));
    CU_ASSERT(bHeap->nodes[3].key == 113); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[3].name , "NodeI", strlen("NodeI"));
    CU_ASSERT(bHeap->nodes[4].key == 115); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[4].name , "NodeH", strlen("NodeH"));
    CU_ASSERT(bHeap->nodes[5].key == 75);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[5].name , "NodeG", strlen("NodeG"));
    CU_ASSERT(bHeap->nodes[6].key == 90);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[6].name , "NodeD", strlen("NodeD"));
    CU_ASSERT(bHeap->nodes[7].key == 95);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[7].name , "NodeE", strlen("NodeE"));
    CU_ASSERT(bHeap->nodes[8].key == 110); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[8].name , "NodeF", strlen("NodeF"));
    CU_ASSERT(bHeap->nodes[9].key == 100); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[9].name , "NodeA", strlen("NodeA"));
    CU_ASSERT(bHeap->nodes[10].key == 60); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[10].name, "NodeL", strlen("NodeL"));
    CU_ASSERT(bHeap->nodes[11].key == 74); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[11].name, "NodeM", strlen("NodeM"));
    CU_ASSERT(bHeap->nodes[12].key == 73); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[12].name, "NodeN", strlen("NodeN"));
    CU_ASSERT(bHeap->nodes[13].key == 70); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[13].name, "NodeO", strlen("NodeO"));
    CU_ASSERT(bHeap->nodes[14].key == 80); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[14].name, "NodeH", strlen("NodeH"));

    // Test peek return
    hNode = peek(bHeap);
    CU_ASSERT(hNode->key == 130); CU_ASSERT_NSTRING_EQUAL (hNode->name, "NodeP", strlen("NodeP"));

    // Test pop return
    poppedNode = pop(&bHeap);
    CU_ASSERT(poppedNode.key == 130); CU_ASSERT_NSTRING_EQUAL (poppedNode.name, "NodeP", strlen("NodeP"));

    // Re-test peek return after pop
    hNode = peek(bHeap);
    CU_ASSERT(hNode->key == 120); CU_ASSERT_NSTRING_EQUAL (hNode->name, "NodeC", strlen("NodeC"));

    // Re-test pop
    poppedNode = pop(&bHeap);
    CU_ASSERT(poppedNode.key == 120); CU_ASSERT_NSTRING_EQUAL (poppedNode.name, "NodeC", strlen("NodeC"));

    for (int i=0; i<4;i++) // remove 4 element
        pop(&bHeap);

    // Assert key/name after pop procedures
    CU_ASSERT(size(bHeap) == 9);
    CU_ASSERT(bHeap->nodes[0].key == 100); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].name, "NodeA", strlen("NodeA"));
    CU_ASSERT(bHeap->nodes[1].key == 95);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[1].name, "NodeE", strlen("NodeE"));
    CU_ASSERT(bHeap->nodes[2].key == 90);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[2].name, "NodeD", strlen("NodeD"));
    CU_ASSERT(bHeap->nodes[3].key == 74);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[3].name, "NodeM", strlen("NodeM"));
    CU_ASSERT(bHeap->nodes[4].key == 70);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[4].name, "NodeO", strlen("NodeO"));
    CU_ASSERT(bHeap->nodes[5].key == 75);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[5].name, "NodeG", strlen("NodeG"));
    CU_ASSERT(bHeap->nodes[6].key == 80);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[6].name, "NodeH", strlen("NodeH"));
    CU_ASSERT(bHeap->nodes[7].key == 60);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[7].name, "NodeL", strlen("NodeL"));
    CU_ASSERT(bHeap->nodes[8].key == 73);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[8].name, "NodeN", strlen("NodeN"));

    for (int i=0; i<8;i++) // remove 8 element
        pop(&bHeap);

    CU_ASSERT(size(bHeap) == 1);
    CU_ASSERT(bHeap->nodes[0].key == 60);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].name, "NodeL", strlen("NodeL"));

    // Test pop procedure when heap has only 1 element
    pop(&bHeap);
    CU_ASSERT(size(bHeap) == 0);

    // Test pop procedure when heap is empty
    poppedNode = pop(&bHeap);
    CU_ASSERT(size(bHeap) == 0);
    CU_ASSERT(poppedNode.key == -1);

    destroy(&bHeap);

    // Test push/peek/size functions with null heap (after destroy being called)
    CU_ASSERT(size(bHeap) == -1);
    CU_ASSERT(push(&bHeap, HeapNodeConstructor(0 , "X")) == -1);
    CU_ASSERT_PTR_NULL(peek(bHeap));
}

int main()
{
   CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("BinaryHeap_TestSuite", NULL, NULL);

   if (pSuite == NULL)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((CU_add_test(pSuite, "Test binary heap creation and destruction", test_create_and_destroy) == NULL) ||
       (CU_add_test(pSuite, "Test binary heap manipulation (pop/push/peek/size)", test_heap_manipulation) == NULL))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}



