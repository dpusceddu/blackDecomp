#ifndef RWA_EE_REQUEST_H
#define RWA_EE_REQUEST_H
#include "rwa_ee/emitter.h"
/* Inferred asynchronous-file and request prefixes from PS2 offsets. */
typedef struct RwaRequestLink {
    struct RwaRequestLink *next,*previous;
    u32 state,position,length,remaining;
    u8 *destination;
    s32 handle;
    u32 field20,result,block_position,block_size;
    u8 *buffer;
    void *owner;
    void (*callback)();
    u32 user;
} RwaRequestLink;
typedef struct RwaAsyncFile {void *driver;u8 prefix[0x40];u32 pending;void (*callback)();u32 user,target;u32 *header;u32 read_header; s32 handle;u32 position;} RwaAsyncFile;
typedef struct RwaCallbackObject {u8 prefix[0x40];u32 flags;u16 kind;} RwaCallbackObject;
#endif
