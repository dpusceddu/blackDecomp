#ifndef BLACK_EFFECTS_EMITTER_LIST_H
#define BLACK_EFFECTS_EMITTER_LIST_H
#include "game/effects/vector.h"
typedef struct BkTimedEmitterNodePS2 {struct BkTimedEmitterNodePS2 *next;f32 time;u8 unknown[0x14];
#ifdef __cplusplus
 bool Alive(f32 now,f32 lifetime) const {return now<time+lifetime;}
#endif
} BkTimedEmitterNodePS2;
typedef struct {char *definition;BkTimedEmitterNodePS2 *head;u16 count;u16 padding;
#ifdef __cplusplus
 bool HasEmitters(void) const {return head!=0;}
#endif
} BkEmitterListPS2;
#endif
