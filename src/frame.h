#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define K_FRAMESIZE 8

typedef uint8_t ybyte;   // 1 byte
typedef uint64_t ylong;  // 8 bytes

// we'll use variable size entries in a frame
// might experiment later with paging inside of frames
// if external fragmentation becomes an issue

struct Frame
{
    ylong LR; // link register
    size_t size;
    void *payload;
};

// returns true on success
bool frame_init(struct Frame *frame_r, size_t size, ylong instlinkaddr);
uint8_t frame_get_var(struct Frame *frame, ylong addr);
bool frame_set_var(struct Frame *frame, ylong addr, ybyte value);
void frame_free(struct Frame *frame);

#endif /* FRAME_H */