#include "CUnit/Basic.h"
#include "tests.h"

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("StackSuite", sstack_init, sstack_clean);
   if (pSuite == NULL) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(pSuite, "test init and free", sstack_shouldInitAndFree)) ||
       (NULL == CU_add_test(pSuite, "test pushing", sstack_shouldPush)) ||
       (NULL == CU_add_test(pSuite, "test popping", sstack_shouldPop))  ||
       (NULL == CU_add_test(pSuite, "test peeking", sstack_shouldPeek)))
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