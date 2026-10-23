#include "rw_audio/sound.h"

extern void func_00317FC0(void *);
extern u8 D_004563A8[];
extern u32 D_0040E188;

void func_00316218(void) {
    func_00317FC0(D_004563A8);
    D_0040E188=0;
}
