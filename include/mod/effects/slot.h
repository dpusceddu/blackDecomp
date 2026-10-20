// Shared mod context; accessed PS2 prefixes only. Original identities and full allocations remain qualified.
#ifndef BLACK_EFFECTS_SLOT_H
#define BLACK_EFFECTS_SLOT_H
#include "game/effects/vector.h"
typedef struct {s16 adjustment;u16 padding;void (*call)(void *,u8);} BkEffectSlotCallbackPS2;
typedef struct {u8 prefix[0x78];BkEffectSlotCallbackPS2 release;} BkEffectSlotVTablePS2;
typedef struct {u8 prefix[0x10];BkEffectSlotVTablePS2 *callbacks;} BkEffectSlottedObjectPS2;
typedef struct {u16 used,write;u16 start,count;BkEffectSlottedObjectPS2 *object;u8 mode,active,padding[2];} BkEffectSlotPS2;
typedef struct {u8 prefix[0xd8];u16 slot;} BkEffectSlotTargetPS2;
#endif
