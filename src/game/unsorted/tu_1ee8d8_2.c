#include "include_asm.h"
#include "ps2/prelude.h"

// Native debug labels occupy consecutive 16-byte-aligned slots.
const s8 D_003F8B00[] __attribute__((section(".rodata.003F8B00"), aligned(16))) = "UpperThreshold";
const s8 D_003F8B10[] __attribute__((section(".rodata.003F8B00"), aligned(16))) = "Low Health";
const s8 D_003F8B20[] __attribute__((section(".rodata.003F8B00"), aligned(16))) = "Full Muff";
const s8 D_003F8B30[] __attribute__((section(".rodata.003F8B00"), aligned(16))) = "Smoothing";
const s8 D_003F8B40[] __attribute__((section(".rodata.003F8B00"), aligned(16))) = "HeartbeatThreshold";

extern s32 func_00280A38(void*, void*, s32);
extern s32 func_00280C90(s32, s32);
extern u8 D_0040DA29;
// UNVERIFIED: original debug registration API; this view preserves native argument banks.
extern s32 func_0027B950(void*, void*, const s8*, const s8*, const s8*, s32, f32, f32, s32);
extern u8* D_003C09E8;
extern f32 D_003BDA1C;
extern s8* D_003BDA08;
extern f32 D_003BDA20;
extern f32 D_003BDA24;
extern f32 D_003BDA28;

s32 func_001EE8D8(void* self, void* resources, s32 count) {
    f32 temp_f20;
    s32 temp_3;
    const s8* temp_16;

    temp_3 = M2C_FIELD(self, s32*, 0x250);
    switch (temp_3) { /* irregular */
        case 2:
        case 0:
            M2C_FIELD(self, s32*, 0x254) = (s32)M2C_FIELD(((void*)((count * 4) + ((s8*)resources))), s32*, -4);
            func_00280A38((void*)self, (void*)resources, count - 1);
            func_00280C90((s32)self, 0);
            M2C_FIELD(self, f32*, 0x26C) = 0.0f;
            M2C_FIELD(self, s8*, 0x290) = 1;
            if (D_0040DA29 == 0) {
                temp_f20 = M2C_FIELD(self, f32*, 0x26C);
                temp_16 = D_003F8B10;
                func_0027B950(D_003C09E8 + 4, &D_003BDA1C, D_003F8B00, temp_16, D_003BDA08, 0, temp_f20, temp_f20, 0);
                func_0027B950(D_003C09E8 + 4, &D_003BDA20, D_003F8B20, temp_16, D_003BDA08, 0, temp_f20, temp_f20, 0);
                func_0027B950(D_003C09E8 + 4, &D_003BDA24, D_003F8B30, temp_16, D_003BDA08, 0, temp_f20, temp_f20, 0);
                func_0027B950(D_003C09E8 + 4, &D_003BDA28, D_003F8B40, temp_16, D_003BDA08, 0, temp_f20, temp_f20, 0);
                D_0040DA29 = 1;
            }
            M2C_FIELD(self, f32*, 0x25C) = 1.0f;
            M2C_FIELD(self, f32*, 0x260) = 0.3f;
            M2C_FIELD(self, f32*, 0x264) = 0.3f;
            M2C_FIELD(self, f32*, 0x268) = 0.15f;
            M2C_FIELD(self, f32*, 0x274) = 3.5f;
            M2C_FIELD(self, f32*, 0x278) = 2.0f;
            M2C_FIELD(self, f32*, 0x27C) = 1.0f;
            M2C_FIELD(self, f32*, 0x280) = 0.5f;
            M2C_FIELD(self, s32*, 0x250) = 1;
            /* fallthrough */
        case 1:
            M2C_FIELD(self, f32*, 0x28C) = -1.0f;
            M2C_FIELD(self, f32*, 0x258) = 1.0f;
            M2C_FIELD(self, s8*, 0x291) = 0;
            break;
    }
    return 1;
}
