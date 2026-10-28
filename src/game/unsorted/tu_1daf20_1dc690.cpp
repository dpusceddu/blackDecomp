#include "ps2/prelude.h"

extern "C" {
extern s32 func_002810A0(void*);
extern s32 func_00280100(void*, void*);
extern void* D_0040F510;
/* The fixed flag array and descending clear retain separate native views. */
static inline u8 (&SlotFlags(void* owner))[64] { return *(u8(*)[64])((u8*)owner + 0x1880); }
void func_001DC690(void* owner, void* value) {
    s32 i = 0;

    while (i < 64 && SlotFlags(owner)[i]) i++;
    M2C_FIELD((u8*)owner + i * 0x60, void**, 0x98) = value;
    M2C_FIELD((u8*)owner + i, u8*, 0x1880) = 1;
    M2C_FIELD((u8*)owner + i * 0x60, s32*, 0x80) = 0;
}

s32 func_001DC6E8(void* owner) {
    s32 i;
    void* handle;
    u8* flags = (u8*)owner + 0x1880;
    u8* clear;
    i = 0;
    handle = (void*)((u8*)owner + 0x84);
    do {
        if (SlotFlags(owner)[i]) func_002810A0(handle);
        i++;
        handle = (void*)((u8*)handle + 0x60);
    } while (i < 64);
    clear = flags + 63;
    for (i = 63; i >= 0; i--) *clear-- = 0;
    return func_00280100(D_0040F510, M2C_FIELD(owner, void**, 0x1934));
}
}
