#ifndef BLACK_GAME_SCRATCHPAD_BUFFERS_H
#define BLACK_GAME_SCRATCHPAD_BUFFERS_H

/* Layout used by the two scratchpad buffers at 0x70002000 and 0x70002800.
 * The original class name is UNVERIFIED. */
typedef struct ScratchpadBuffers {
    unsigned int addresses[2];
    int currentIndex;
} ScratchpadBuffers;

typedef char ScratchpadBuffersSize[sizeof(ScratchpadBuffers) == 12 ? 1 : -1];

#endif
