#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_004494D4)();
extern s32 func_002AC6E8(s32);
extern s32 func_002A8688();
extern s32 func_002A7DD0();
extern s32 func_002A8DA0();
extern s32 func_002A8860();
extern void * func_002D0910();
extern s32 func_002CFAC0();
extern M2C_UNK D_003C3210;

/* PS2 camera, engine, image and frame models within this provisional grouping. */

















INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A8F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9640);
#ifdef NON_MATCHING
typedef struct RwErrorPS2 {s32 plugin,code;} RwErrorPS2;
extern u8 D_00449438[];extern s32 D_0040DF14;
extern s32 func_002A5548(s32,...);extern void func_002A55D8(RwErrorPS2 *);extern void *func_002BFE58(void);
extern s32 func_002A9F08(void *,s32,void *,void *,s32);
// Unmatched: compiler control flow, aggregate lifetime and scheduling still differ.
s32 func_002A9B70(void *parameters) {
 void *device;
 if(M2C_FIELD(D_00449438,s32 *,0x124)!=1) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000001);func_002A55D8(&error);return 0;}
 if(!parameters) {RwErrorPS2 error;error.plugin=1;error.code=func_002A5548(0x80000016);func_002A55D8(&error);return 0;}
 device=func_002BFE58();if(!device)return 0;
 func_002A9F08(device,4,D_00449438+0x10,D_00449438+0x108,0);
 if(!func_002A9F08(device,0,0,parameters,0))return 0;
 func_002A9F08(device,11,D_00449438+0x48,0,29);D_0040DF14++;M2C_FIELD(D_00449438,s32 *,0x124)=2;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9B70);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9CB8);

void func_002A90C8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x18)();
}

void func_002A90E8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x1C)();
}

s32 func_002A9108(s32 arg0) {
    return (D_004494D4() == 0) ? 0 : arg0;
}

void * func_002A9140(void *arg0) {
    return (func_002AC6E8(M2C_FIELD(arg0, s32 *, 0x60)) == 0) ? NULL : arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A91D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9310);

#include "ps2/recovered_types.h"
extern s32 func_002CFAC0(void *, u32, u32, u32, u32, s32);
extern s32 D_003C31F8;

s32 func_002A93E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_002CFAC0(&D_003C31F8, (u32) arg0, (u32) arg1, (u32) arg2, (u32) arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9498);

void * func_002A9518(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x14) == 1) {
        func_002A8688();
        func_002A7DD0(arg0);
    } else {
        func_002A8DA0(arg0);
        func_002A8860(arg0);
    }
    func_002D0910(arg0 + 0x10C, arg0 + 0x124, 8);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A95E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9830);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A98A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A99D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9AE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9CB0);

s32 func_002A9DF0(s32 size, s32 plugin_id, s32 construct, s32 destroy) {
    return func_002CFAC0(&D_003C3210, size, plugin_id, construct, destroy, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2a8f78", func_002A9E30);
