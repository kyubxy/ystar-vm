#ifndef FRAME_H
#define FRAME_H

// we'll use variable size entries in a frame
// might experiment later with paging inside of frames
// if external fragmentation becomes an issue

struct Frame
{
    void *ptr;
};

int frame_free(void *frame);

#endif /* FRAME_H */