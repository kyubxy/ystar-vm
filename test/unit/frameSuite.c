#include <frame.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

void sframe_shouldInitAndFree(void)
{
    ylong addr = 0x42426969;
    struct Frame f; 
    frame_init(&f, 100, addr);
    CU_ASSERT_EQUAL(addr, f.LR);
    frame_free(&f);
}

void sframe_shouldSetVar(void)
{
    struct Frame f; 
    frame_init(&f, 100, 0);
    frame_set_var(&f, 0x00, 69);
    frame_set_var(&f, 0x01, 42);
    frame_set_var(&f, 0x02, 1);
    frame_free(&f);
    CU_ASSERT_TRUE(1);
}

void sframe_shouldGetVar(void)
{
    struct Frame f; 
    frame_init(&f, 100, 0);
    frame_set_var(&f, 0x00, 69);
    frame_set_var(&f, 0x01, 42);
    frame_set_var(&f, 0x02, 1);
    CU_ASSERT_EQUAL(69, frame_get_var(&f, 0x00));
    CU_ASSERT_EQUAL(42, frame_get_var(&f, 0x01));
    CU_ASSERT_EQUAL( 1, frame_get_var(&f, 0x02));
    frame_free(&f);
}

