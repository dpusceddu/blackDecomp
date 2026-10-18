#ifndef RWA_EE_PROPERTY_H
#define RWA_EE_PROPERTY_H
#include "rwa_ee/emitter.h"
/* Inferred PS2 property metadata and value objects. */
typedef struct RwaProperty {u32 id,type,state;u32 descriptor[2];} RwaProperty;
typedef struct RwaPropertyClass {u32 prefix[3];RwaProperty *output,*input;u16 input_count,output_count;u32 flags;} RwaPropertyClass;
typedef struct RwaValueLink {struct RwaValueLink *next,*previous;} RwaValueLink;
typedef struct RwaValueList {s32 count;RwaValueLink link;} RwaValueList;
typedef struct RwaValue {void *next,*previous;u32 tag;void *input,*output;u32 type;struct RwaValue *parent;u32 flags;RwaValueLink link;} RwaValue;
typedef struct RwaValueSpec {const char *name;u32 type,size;u8 *data;u32 id;const char *parent;RwaValue *object;u8 *storage;} RwaValueSpec;
typedef struct RwaValuePool {RwaPool *pool;u32 size;} RwaValuePool;
#endif
