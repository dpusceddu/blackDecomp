#ifndef RWA_EE_BANK_H
#define RWA_EE_BANK_H
#include "auto/prelude.h"

/* Inferred names; accessed bank and disk-header offsets are verified by matching users.
   This bank view does not establish the complete bank size.
   Stream offsets remain an access view, pending a matching typed user. */
typedef struct RwaBank RwaBank;
typedef struct RwaStream RwaStream;
typedef struct RwaLink { struct RwaLink *previous, *next; void *object; } RwaLink;
struct RwaBank {
    u32 tag;
    void *name;
    u32 size;
    RwaLink *list_previous;
    RwaLink *first;
    void *last;
    u16 id;
    u8 flags1a, flags1b;
    RwaBank *next;
    RwaBank **previous;
    void *allocation;
    void *data;
    u32 data_size;
    u32 field30;
    u32 field34;
    u32 field38;
    u32 field3c;
    u32 field40;
};
struct RwaStream {
    RwaBank *bank;
    s32 handle;
    u32 read_size;
    u32 format;
    void *buffer;
    u32 capacity;
    u32 flags;
    void *data;
    u32 data_size;
    u32 position;
    u32 remaining;
    u32 state;
    u32 ownership;
    u32 block_size;
    u32 field38;
    u32 field3c;
    u32 cursor;
    u32 mode;
};
typedef struct {s64 a,b;} __attribute__((packed)) RwaIdBytes;
typedef struct RwaDiskHeader {
    u32 tag;
    u8 endian,version,flags,format;
    u32 size,bank_offset,field10,bank_size;
    u8 bank_id[16];
    u32 field28;
} RwaDiskHeader;
#endif
