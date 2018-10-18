#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <CUnit/Basic.h>

#include "binary_heap.h"


// Useful method to construct and return a node with a given key and name
HeapNode HeapNodeConstructor(int key, char* name)
{
    HeapNode hNode;
    hNode.key = key;
    hNode.item = malloc ((strlen(name) + 1) * sizeof(char));
    strcpy(hNode.item, name);
    return hNode;
}

void test_create_and_destroy(void)
{
  BinaryHeap* bHeap = binary_heap_create(free);
  CU_ASSERT_PTR_NOT_NULL(bHeap);
  CU_ASSERT_PTR_NULL(bHeap->nodes);
  CU_ASSERT(bHeap->size == 0);
  binary_heap_destroy(&bHeap);
  CU_ASSERT_PTR_NULL(bHeap);
}

void test_heap_manipulation()
{
    HeapNode* hNode = NULL;
    HeapNode poppedNode;
    BinaryHeapCollector collector = free; // use free when deallocating heap items.
    BinaryHeap* bHeap = binary_heap_create(collector);

    binary_heap_push(&bHeap, HeapNodeConstructor(100, "NodeA")); // 1
    binary_heap_push(&bHeap, HeapNodeConstructor(120, "NodeC")); // 2
    binary_heap_push(&bHeap, HeapNodeConstructor(90 , "NodeD")); // 3
    binary_heap_push(&bHeap, HeapNodeConstructor(95 , "NodeE")); // 4
    binary_heap_push(&bHeap, HeapNodeConstructor(110, "NodeF")); // 5
    binary_heap_push(&bHeap, HeapNodeConstructor(75 , "NodeG")); // 6
    binary_heap_push(&bHeap, HeapNodeConstructor(80 , "NodeH")); // 7
    binary_heap_push(&bHeap, HeapNodeConstructor(115, "NodeH")); // 8
    binary_heap_push(&bHeap, HeapNodeConstructor(113, "NodeI")); // 9
    binary_heap_push(&bHeap, HeapNodeConstructor(116, "NodeJ")); // 10
    binary_heap_push(&bHeap, HeapNodeConstructor(60 , "NodeL")); // 11
    binary_heap_push(&bHeap, HeapNodeConstructor(74 , "NodeM")); // 12
    binary_heap_push(&bHeap, HeapNodeConstructor(73 , "NodeN")); // 13
    binary_heap_push(&bHeap, HeapNodeConstructor(70 , "NodeO")); // 14
    binary_heap_push(&bHeap, HeapNodeConstructor(130, "NodeP")); // 15

    // Assert key/name after push procedures
    CU_ASSERT(bHeap->size == 15);
    CU_ASSERT(bHeap->nodes[0].key == 130); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].item , "NodeP", strlen("NodeP"));
    CU_ASSERT(bHeap->nodes[1].key == 116); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[1].item , "NodeJ", strlen("NodeJ"));
    CU_ASSERT(bHeap->nodes[2].key == 120); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[2].item , "NodeC", strlen("NodeC"));
    CU_ASSERT(bHeap->nodes[3].key == 113); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[3].item , "NodeI", strlen("NodeI"));
    CU_ASSERT(bHeap->nodes[4].key == 115); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[4].item , "NodeH", strlen("NodeH"));
    CU_ASSERT(bHeap->nodes[5].key == 75);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[5].item , "NodeG", strlen("NodeG"));
    CU_ASSERT(bHeap->nodes[6].key == 90);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[6].item , "NodeD", strlen("NodeD"));
    CU_ASSERT(bHeap->nodes[7].key == 95);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[7].item , "NodeE", strlen("NodeE"));
    CU_ASSERT(bHeap->nodes[8].key == 110); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[8].item , "NodeF", strlen("NodeF"));
    CU_ASSERT(bHeap->nodes[9].key == 100); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[9].item , "NodeA", strlen("NodeA"));
    CU_ASSERT(bHeap->nodes[10].key == 60); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[10].item, "NodeL", strlen("NodeL"));
    CU_ASSERT(bHeap->nodes[11].key == 74); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[11].item, "NodeM", strlen("NodeM"));
    CU_ASSERT(bHeap->nodes[12].key == 73); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[12].item, "NodeN", strlen("NodeN"));
    CU_ASSERT(bHeap->nodes[13].key == 70); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[13].item, "NodeO", strlen("NodeO"));
    CU_ASSERT(bHeap->nodes[14].key == 80); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[14].item, "NodeH", strlen("NodeH"));

    // Test peek return
    hNode = binary_heap_peek(bHeap);
    CU_ASSERT(hNode->key == 130); CU_ASSERT_NSTRING_EQUAL (hNode->item, "NodeP", strlen("NodeP"));

    // Test pop return
    poppedNode = binary_heap_pop(&bHeap);
    CU_ASSERT(poppedNode.key == 130); CU_ASSERT_NSTRING_EQUAL (poppedNode.item, "NodeP", strlen("NodeP"));

    // Re-test peek return after pop
    hNode = binary_heap_peek(bHeap);
    CU_ASSERT(hNode->key == 120); CU_ASSERT_NSTRING_EQUAL (hNode->item, "NodeC", strlen("NodeC"));

    // Re-test pop
    poppedNode = binary_heap_pop(&bHeap);
    CU_ASSERT(poppedNode.key == 120); CU_ASSERT_NSTRING_EQUAL (poppedNode.item, "NodeC", strlen("NodeC"));

    for (int i=0; i<4;i++) { // remove 4 element
        binary_heap_pop(&bHeap);
    }

    // Assert key/name after pop procedures
    CU_ASSERT(bHeap->size == 9);
    CU_ASSERT(bHeap->nodes[0].key == 100); CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].item, "NodeA", strlen("NodeA"));
    CU_ASSERT(bHeap->nodes[1].key == 95);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[1].item, "NodeE", strlen("NodeE"));
    CU_ASSERT(bHeap->nodes[2].key == 90);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[2].item, "NodeD", strlen("NodeD"));
    CU_ASSERT(bHeap->nodes[3].key == 74);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[3].item, "NodeM", strlen("NodeM"));
    CU_ASSERT(bHeap->nodes[4].key == 70);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[4].item, "NodeO", strlen("NodeO"));
    CU_ASSERT(bHeap->nodes[5].key == 75);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[5].item, "NodeG", strlen("NodeG"));
    CU_ASSERT(bHeap->nodes[6].key == 80);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[6].item, "NodeH", strlen("NodeH"));
    CU_ASSERT(bHeap->nodes[7].key == 60);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[7].item, "NodeL", strlen("NodeL"));
    CU_ASSERT(bHeap->nodes[8].key == 73);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[8].item, "NodeN", strlen("NodeN"));

    for (int i=0; i<8;i++) { // remove 8 element
        binary_heap_pop(&bHeap);
    }

    CU_ASSERT(bHeap->size == 1);
    CU_ASSERT(bHeap->nodes[0].key == 60);  CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].item, "NodeL", strlen("NodeL"));

    // Test pop procedure when heap has only 1 element
    binary_heap_pop(&bHeap);
    CU_ASSERT(bHeap->size == 0);

    // Test pop procedure when heap is empty
    poppedNode = binary_heap_pop(&bHeap);
    CU_ASSERT(bHeap->size == 0);
    CU_ASSERT(poppedNode.key == -1);

    binary_heap_destroy(&bHeap);

    // Test push/peek/size functions with null heap (after destroy being called)
    CU_ASSERT(bHeap->size == -1);
    CU_ASSERT(binary_heap_push(&bHeap, HeapNodeConstructor(0 , "X")) == -1);
    CU_ASSERT_PTR_NULL(binary_heap_peek(bHeap));
}

int main()
{
   CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry()) {
      return CU_get_error();
   }

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



