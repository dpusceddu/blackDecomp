#ifndef GAME_VALUE_RATIO_H
#define GAME_VALUE_RATIO_H
#include "ps2/prelude.h"

typedef struct {
    s16 adjustment;
    u16 unk_02;
    f32 (*call)(void*);
} Recovered_ValueRatioFloatMethod;

typedef struct {
    s16 adjustment;
    u16 unk_02;
    s32 (*call)(void*);
} Recovered_ValueRatioIntMethod;

typedef struct {
    u8 unk_00[0x28];
    Recovered_ValueRatioFloatMethod denominator;
    Recovered_ValueRatioIntMethod numerator;
} Recovered_ValueRatioMethods;

/* The two virtual calls establish the ratio operation. The original class
 * identity and meanings of the initialized prefix fields are UNVERIFIED. */
typedef struct {
    u64 unk_00;
    u32 unk_08;
    u8 unk_0C, unk_0D;
    u16 unk_0E;
    Recovered_ValueRatioMethods* methods;
} Recovered_ValueRatioSource;

typedef char ValueRatioMethodsOffset[(u32)&((Recovered_ValueRatioSource*)0)->methods == 0x10 ? 1 : -1];
void ValueRatio_Initialize(Recovered_ValueRatioSource* self);
f32 ValueRatio_Get(Recovered_ValueRatioSource* self);
#endif
