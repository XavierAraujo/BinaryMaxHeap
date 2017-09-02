#include <stdio.h>
#include <string.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

#include "binary_heap.h"


void test_create(void)
{
  binaryHeap* bHeap = create();
  CU_ASSERT_PTR_NOT_NULL(bHeap);
  CU_ASSERT_PTR_NULL(bHeap->nodes);
  CU_ASSERT(bHeap->size == 0);
  destroy(&bHeap);
}

void test_size(void)
{
  binaryHeap* bHeap = create();
  CU_ASSERT(size(bHeap) == 0);
  bHeap->size = 2;
  CU_ASSERT(size(bHeap) == 2);
  bHeap->size = 10;
  CU_ASSERT(size(bHeap) == 10);

  destroy(&bHeap);
}

void test_push()
{
    binaryHeap* bHeap = create();
    heapNode hNode;

    hNode.key = 100; strcpy(hNode.name, "NodeA");
    push(&bHeap, hNode);
    CU_ASSERT(size(bHeap) == 1);
    CU_ASSERT_PTR_NOT_NULL(bHeap->nodes);
    CU_ASSERT(bHeap->nodes[0].key == 100);
    CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].name, "NodeA", strlen("NodeA"));

    hNode.key = 110; strcpy(hNode.name, "NodeB");
    push(&bHeap, hNode);
    CU_ASSERT(size(bHeap) == 2);
    CU_ASSERT(bHeap->nodes[0].key == 110);
    CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].name, "NodeB", strlen("NodeB"));
    CU_ASSERT(bHeap->nodes[1].key == 100);
    CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[1].name, "NodeA", strlen("NodeA"));

    hNode.key = 90; strcpy(hNode.name, "NodeC");
    push(&bHeap, hNode);
    CU_ASSERT(size(bHeap) == 3);
    CU_ASSERT(bHeap->nodes[0].key == 110);
    CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[0].name, "NodeB", strlen("NodeB"));
    CU_ASSERT(bHeap->nodes[1].key == 100);
    CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[1].name, "NodeA", strlen("NodeA"));
    CU_ASSERT(bHeap->nodes[2].key == 90);
    CU_ASSERT_NSTRING_EQUAL (bHeap->nodes[2].name, "NodeC", strlen("NodeC"));

    destroy(&bHeap);
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

   if ((CU_add_test(pSuite, "Test heap creation", test_create) == NULL) ||
       (CU_add_test(pSuite, "Test heap's size obtainment", test_size) == NULL) ||
       (CU_add_test(pSuite, "Test heap push", test_push) == NULL))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}



