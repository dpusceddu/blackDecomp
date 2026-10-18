#ifndef RWA_EE_OBJECT_H
#define RWA_EE_OBJECT_H
#include "rwa_ee/property.h"
/* Inferred object/class access prefixes from PS2 offsets. */
typedef struct RwaObject RwaObject;
typedef struct RwaClass RwaClass;
typedef RwaObject *(*RwaObjectAllocator)(RwaClass *,void *,void *,u32);
typedef struct RwaPropertyCounts {u8 prefix[12];u16 input,output;} RwaPropertyCounts;
struct RwaClass {
    const void *id;u8 prefix04[0x24];
    s32 (*construct)(RwaObject *,void *,void *,RwaObjectAllocator,void *);
    u8 prefix2c[0x10];
    void (*defaults)(s32,void *);
    u32 extent_alignment;u16 defaults_size,padding46;
    void *field48;RwaPropertyCounts *properties;
};
struct RwaObject {
    RwaClass *type;
    RwaValueLink global_link,property_link,owner_link;
    u32 flags;
    u8 *data;
    void *owner;
};
typedef struct RwaObjectOwner {RwaClass *type;u8 prefix04[8];RwaValueLink objects;} RwaObjectOwner;
typedef struct RwaObjectProperty {RwaValueLink link;struct RwaObjectProperty *self;} RwaObjectProperty;
typedef struct RwaObjectProperties {RwaObjectProperty *input;RwaValueLink *output;} RwaObjectProperties;
typedef struct RwaConnection {u8 prefix[12];RwaValueLink output_link,input_link;} RwaConnection;
#endif
