#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "rw_audio/sample.h"

extern s32 func_0036D518();
extern s32 (*D_003D113C)();
extern s32 func_0036D568();
extern void func_00329710();

extern Recovered_AudioHandlePool D_0045C120;
extern u32 D_003D1138;
extern u8 D_004092D0[];
extern u8 D_004092E0[];
extern const Recovered_AudioFormat D_004097B4;
extern s32 func_00316400(void*, void*);

void func_00328E60(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    func_0036D518();
    if (D_003D113C != NULL) {
        D_003D113C(*(s32 *)(sp + 0));
        func_0036D568();
        return;
    }
    func_00329710(&D_0045C120, sp);
    func_0036D568();
}

void* AudioHandle_Resolve(u32 handle) {
    if (!D_003D1138) {
        return (void*)((handle & ((1 << D_0045C120.indexBits) - 1)) * D_0045C120.stride + (u32)D_0045C120.storage);
    }
    return (void*)handle;
}
#ifdef NON_MATCHING
// Unmatched: instruction comparison passes; owned descriptor has excess alignment.
u32 AudioSample_FrameCount(Recovered_AudioSample* sample) {
    u32 bytes = sample->encodedBytes;
    u32 frames = 0;
    if (func_00316400(sample->format, D_004092D0) == 0) {
        switch (sample->channels) {
            case 1:
                frames = bytes >> 4;
                frames *= 28;
                break;
            case 2:
                frames = bytes >> 4;
                frames *= 28;
                frames >>= 1;
                break;
        }
    } else if (func_00316400(sample->format, D_004092E0) == 0 && sample->bitsPerSample == D_004097B4.bitsPerSample) {
        switch (sample->channels) {
            case 1: frames = bytes >> 1; break;
            case 2: frames = bytes >> 2; break;
        }
    }
    return frames;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_328e60", func_00328F00);
#endif

#ifdef NON_MATCHING
/* Native default format descriptor; this TU reads only its 16-bit width byte. */
const Recovered_AudioFormat D_004097B4 __attribute__((aligned(4))) = {16, {1, 0, 0}, {1, 0xFFFFFFFF, 0, 0}};
#endif
