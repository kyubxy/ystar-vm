#include <sys/mman.h>
#include <stddef.h>
#include <stdlib.h>
#include "frame.h"

// some pointer shitfuckery
#define GET(frame, addr) ((uint8_t*)((void*)frame->payload + addr))

// places the frame at the specific location
bool frame_init(struct Frame *frame_r, size_t size, ylong instlinkaddr)
{
    frame_r->LR = instlinkaddr;
    frame_r->size = size;
    frame_r->payload = (struct Frame*)mmap(NULL, size, PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    return true;
}

uint8_t frame_get_var(struct Frame *frame, ylong addr)
{
    return *GET(frame, addr); 
}

bool frame_set_var(struct Frame *frame, ylong addr, ybyte value)
{
    if (addr > (size_t)(frame->payload + frame->size))
        return false; // out of range
    *GET(frame, addr) = value;
    return true;
}

void frame_free(struct Frame *frame)
{
    if (frame != NULL)
        munmap(frame, frame->size);
}