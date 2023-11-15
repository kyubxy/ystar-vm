#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

#define K_FRAMESIZE 8

// we'll use variable size entries in a frame
// might experiment later with paging inside of frames
// if external fragmentation becomes an issue

struct Frame
{
    uint32_t returnaddr;
    uint32_t *ptr;
};

int frame_init(struct Frame *frame_o, uint32_t retAddr);
int frame_get_var(struct Frame *frame, int addr, uint32_t *dest);
int frame_set_var(struct Frame *frame, int addr, uint32_t value);
int frame_free(void *frame);

#endif /* FRAME_H */