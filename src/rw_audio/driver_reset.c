#include "rw_audio/sound.h"

extern void *func_0031E0E0(void *,void *,void *,s32,s32);
extern void func_003156C8(void);
extern void func_00317FC0(void *);
extern u8 D_00456380[];
extern u32 D_0040E184;

void func_00315598(void) {
    func_0031E0E0(0,0,(void *)func_003156C8,0,1);
    func_00317FC0(D_00456380);
    D_0040E184=0;
}
