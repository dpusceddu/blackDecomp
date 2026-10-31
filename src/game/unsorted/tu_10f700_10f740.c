#include "include_asm.h"
#include "ps2/prelude.h"
// Local controller access view; original class and callback identities are UNVERIFIED.
extern void func_0027CF78(void*, s32, const void*, s32);
extern void* D_0040F0E0;
extern void func_0027A798(void*);
extern void func_0010F700(void*);
extern void* func_0027D118(void*, u64);

f32 func_0010F740(void *arg0) {
    return M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0) << 6) + M2C_FIELD(arg0, s32 *, 0x18)), f32 *, -0x40);
}

// Native read-only input combines this state table with camera-path export formats.
// Their original source organization is UNVERIFIED. Each format has native 8-byte alignment.
typedef struct ControllerStateOffset {
    u64 key;
    s32 offset;
} ControllerStateOffset;
typedef char ControllerStateOffsetIs16[(sizeof(ControllerStateOffset) == 16) ? 1 : -1];
const ControllerStateOffset D_003F3B90[] = {
    {0x594C3BB5A28A38A1UL, 0x18},  {0x594C3B3ED729E1C6UL, 0x30},
    {0x594C3AEE53B27048UL, 0x40},  {0x594C3D53EF90903FUL, 0xB0},
    {0x594C3BFD6D9FF5E1UL, 0xD0},  {0x594C3CC765B41051UL, 0x160},
    {0x594C3BF9EB754139UL, 0x140}, {0, 0},
};
const char RecoveredCameraPathSuffix[] __attribute__((aligned(8))) = ".keyframes";
const char RecoveredCameraPathBegin[] __attribute__((aligned(8))) = "<camerapath keyframes=\"%d\" effects=\"%d\">\n";
const char RecoveredCameraKeyframeBegin[] __attribute__((aligned(8))) =
    "\t<keyframe fov=\"%f\" time=\"%f\" effects=\"%d\">\n";
const char RecoveredCameraPositionFormat[] __attribute__((aligned(8))) = "\t\t<position x=\"%f\" y=\"%f\" z=\"%f\"/>\n";
const char RecoveredCameraOrientationFormat[] __attribute__((aligned(8))) =
    "\t\t<orientation a=\"%f\" b=\"%f\" c=\"%f\" d=\"%f\"/>\n";
const char RecoveredCameraKeyframeEnd[] __attribute__((aligned(8))) = "\t</keyframe>\n";
const char RecoveredCameraEffectBegin[] __attribute__((aligned(8))) =
    "\t<effect type=\"%d\" magnitude=\"%f\"  time1=\"%f\" time2=\"%f\" time3=\"%f\" time4=\"%f\" >\n";
const char RecoveredCameraEffectEnd[] __attribute__((aligned(8))) = "\t</effect>\n";
const char RecoveredCameraPathEnd[] __attribute__((aligned(8))) = "</camerapath>\n";

s32 func_0010F758(void* arg0) {
    s32 enabled;
    void* temp_2;
    void* temp_2_2;
    void* temp_2_3;
    void* temp_2_4;
    void* temp_5;

    func_0027CF78(arg0, (s32)arg0, D_003F3B90, (s32)((void*)(((s8*)D_0040F0E0) + 0x20120)));
    func_0027A798((void*)(((s8*)arg0) + 0x700));
    func_0027A798((void*)(((s8*)arg0) + 0x750));
    func_0010F700((u8*)arg0 + 0x7F0);
    temp_2 = func_0027D118(arg0, 0x594C3BB5A28A38A1UL);
    if (M2C_FIELD(arg0, void**, 0) != temp_2) {
        temp_2_2 = M2C_FIELD(arg0, void**, 0x14);
        M2C_FIELD(temp_2_2, void (**)(void*, void*, s32), 0x2C)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_2, s16*, 0x28)),
                                                                temp_2, 0);
        temp_5 = M2C_FIELD(arg0, void**, 0);
        temp_2_3 = M2C_FIELD(arg0, void**, 0xC);
        M2C_FIELD(arg0, void**, 0) = temp_2;
        if (temp_2_3 != NULL) {
            M2C_FIELD(arg0, f32*, 0x10) = (f32)M2C_FIELD(temp_2_3, f32*, 0x20);
            if (temp_2 != NULL) { M2C_FIELD(temp_2, f32*, 8) = (f32)M2C_FIELD(temp_2_3, f32*, 0x20); }
        }
        temp_2_4 = M2C_FIELD(arg0, void**, 0x14);
        M2C_FIELD(temp_2_4, void (**)(void*, void*, s32), 0x34)((void*)(((s8*)arg0) + M2C_FIELD(temp_2_4, s16*, 0x30)),
                                                                temp_5, 0);
    }
    enabled = 1;
    M2C_FIELD(arg0, s8*, 0x1664) = enabled;
    M2C_FIELD(arg0, s32*, 0x1668) = 3;
    M2C_FIELD(arg0, s64*, 0x6F0) = 0;
    M2C_FIELD(arg0, s8*, 0x7E1) = 0;
    M2C_FIELD(arg0, s8*, 0x7E2) = 0;
    return enabled;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_10f740", func_0010F860);
