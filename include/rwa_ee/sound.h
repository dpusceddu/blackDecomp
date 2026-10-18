#ifndef RWA_EE_SOUND_H
#define RWA_EE_SOUND_H
#include "rwa_ee/bank.h"

/* Inferred names. Matching serializers verify the format and sound layouts.
   The driver remains a partial PS2 access view. Format IDs are 16-byte values. */
typedef struct RwaFormatId {u32 words[4];} RwaFormatId;
typedef struct RwaFormat {
    u32 rate;
    const RwaFormatId *encoding;
    void *codec;
    u8 bits,channels;
    u16 padding0e;
    void *extension;
    u32 extension_size;
    u8 flags,field19;
    u16 padding1a;
} RwaFormat;
typedef struct RwaPackedFormat {RwaFormat value;} __attribute__((packed)) RwaPackedFormat;
typedef struct RwaObjectHeader {void *next,*previous;u32 tag;} __attribute__((packed)) RwaObjectHeader;
typedef struct RwaSound RwaSound;
typedef struct RwaSoundDriver {
    void *slots00[3];
    s32 (*initialize)(RwaSound *,void *);
    void *slot10;
    RwaSound *(*process)(RwaSound *,u32,void *,u32);
    void *slots18[7];
    u32 format_count;
    RwaFormat **formats;
    u32 format_index;
    u32 field40;
    u32 work_size;
    u32 field48;
    void *pool;
} RwaSoundDriver;
struct RwaSound {
    RwaObjectHeader object;
    RwaSoundDriver *driver;
    RwaFormat source_format,output_format;
    u32 field48,field4c;
    void *work;
    u32 flags;
    void *user;
};
#endif
