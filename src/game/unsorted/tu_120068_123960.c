#include "include_asm.h"
#include "ps2/prelude.h"

extern void** D_0040F4DC;
extern s64 func_002902F8(f32);
extern void* D_0040F4D0;
extern s16 func_00122368(void*, s32);
extern s32 func_00123B80(s32, s32);


extern void func_00123988(void*);

void func_00123960(void* self) {
    func_00123988(self);
}

s32 func_00123980(void) {
    return 0;
}

void func_00123988(void* self) {
    s16 count;
    s32 total;
    s32 otherTotal;
    u64 second;
    u64 first;
    void* stats;

    stats = *D_0040F4DC;
    total = M2C_FIELD(self, s32*, 0x408) + (s16)(M2C_FIELD(stats, u16*, 0x1C) + M2C_FIELD(stats, u16*, 0x1E));
    M2C_FIELD(self, s32*, 0x408) = total;
    count = M2C_FIELD(*D_0040F4DC, s16*, 0x2A);
    otherTotal = M2C_FIELD(self, s32*, 0x40C) + count;
    M2C_FIELD(self, s32*, 0x40C) = otherTotal;
    M2C_FIELD(self, s64*, 0x520) =
        (s64)(M2C_FIELD(self, s64*, 0x520) + func_002902F8(M2C_FIELD(D_0040F4D0, f32*, 0x20)));
    if (func_00122368(D_0040F4DC, 0x20) > 0) { func_00123B80((s32)self, 0); }
    if (func_00122368(D_0040F4DC, 0x200) > 0) { func_00123B80((s32)self, 1); }
    if (func_00122368(D_0040F4DC, 0x10) > 0) { func_00123B80((s32)self, 2); }
    if (func_00122368(D_0040F4DC, 0x400) > 0) { func_00123B80((s32)self, 3); }
    if (func_00122368(D_0040F4DC, 0x800) > 0) { func_00123B80((s32)self, 4); }
    if (func_00122368(D_0040F4DC, 0x1000) > 0) { func_00123B80((s32)self, 5); }
    if (func_00122368(D_0040F4DC, 4) > 0) { func_00123B80((s32)self, 6); }
    if ((func_00122368(D_0040F4DC, 2) > 0) || (func_00122368(D_0040F4DC, 8) > 0)) { func_00123B80((s32)self, 7); }
    if (func_00122368(D_0040F4DC, 0x40) > 0) { func_00123B80((s32)self, 8); }
    first = M2C_FIELD(self, u64*, 0x410) + M2C_FIELD(*D_0040F4DC, u32*, 0x48);
    M2C_FIELD(self, u64*, 0x410) = first;
    if (first > 0x98967FU) { M2C_FIELD(self, u64*, 0x410) = 0x98967FU; }
    second = M2C_FIELD(self, u64*, 0x518) + M2C_FIELD(*D_0040F4DC, u32*, 0x4C);
    M2C_FIELD(self, u64*, 0x518) = second;
    if (second > 0x98967FU) { M2C_FIELD(self, u64*, 0x518) = 0x98967FU; }
}
