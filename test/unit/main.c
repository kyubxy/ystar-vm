#include "CUnit/Basic.h"
#include "tests.h"

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   // initialise cunit
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   // stack
   pSuite = CU_add_suite("StackSuite", NULL, NULL);
   if (pSuite == NULL) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pSuite, "test init and free", sstack_shouldInitAndFree)) ||
       (NULL == CU_add_test(pSuite, "test pushing", sstack_shouldPush)) ||
       (NULL == CU_add_test(pSuite, "test popping", sstack_shouldPop))  ||
       (NULL == CU_add_test(pSuite, "test peeking", sstack_shouldPeek)) ||
       (NULL == CU_add_test(pSuite, "test old data payloads preserved", sstack_shouldNotInterfereOnPush)) ||
       (NULL == CU_add_test(pSuite, "test null pointer on pop", sstack_shouldPopIgnoreNull)) ||
       (NULL == CU_add_test(pSuite, "test pop then push", sstack_shouldPopResume))
       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // frame
   pSuite = CU_add_suite("FrameSuite", NULL, NULL);
   if (pSuite == NULL) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pSuite, "test init and free", sframe_shouldInitAndFree)) ||
       (NULL == CU_add_test(pSuite, "test setting variable", sframe_shouldSetVar)) ||
       (NULL == CU_add_test(pSuite, "test getting variable", sframe_shouldGetVar)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}