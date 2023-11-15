#include <stdlib.h>
#include <string.h>
#include "frame.h"
#include "errcodes.h"

int frame_init(struct Frame *frame, uint32_t retAddr)
{
    frame = malloc(sizeof(struct Frame));
    frame->ptr = malloc(K_FRAMESIZE * 1000);
    if (frame == NULL || frame->ptr == NULL)
        return -E_SYSCALL;
    frame->returnaddr = retAddr;
    return E_OK;
}

int frame_get_var(struct Frame *frame, int addr, uint32_t *dest)
{
    *dest = frame->ptr[addr];
    return E_OK;
}

int frame_set_var(struct Frame *frame, int addr, uint32_t value)
{
    memcpy(frame->ptr[addr], &value, sizeof(uint32_t));
    return E_OK;
}

int frame_free(void *frame)
{
    free(((struct Frame*)frame)->ptr);
    free(frame);
    return E_OK;
}
