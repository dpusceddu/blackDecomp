#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00289398();
extern void *func_0035C544(void *, const void *, u32);

typedef struct {
    void *vtable;
    void *source;
    u32 remaining;
    const u8 *cursor;
} Recovered_BoundedStream; /* Original stream identity UNVERIFIED. */
extern M2C_UNK D_003E29A8;
extern int D_003E0040;
extern void (*D_003C87E0)(void *);

s32 func_00288BC8(s32 arg0) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_2 != 0) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) (temp_2 + arg0);
    }
    temp_2_2 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_2_2 != 0) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_2_2 + arg0);
    }
    temp_2_3 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_2_3 != 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) (temp_2_3 + arg0);
    }
    return func_00289398(M2C_FIELD(arg0, s32 *, 4));
}

void * func_00288C18(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E29A8;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    return arg0;
}

void func_00288C38(void **arg0, int arg1)
{
    *arg0 = &D_003E0040;
    if (arg1 & 1) D_003C87E0(arg0);
}

s32 func_00288C70(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 8);
    return 1;
}

u32 func_00288C90(Recovered_BoundedStream *stream, s32 unused, void *destination, u32 requested) {
    u32 size = stream->remaining < requested ? stream->remaining : requested;
    func_0035C544(destination, stream->cursor, size);
    stream->cursor += size;
    stream->remaining -= size;
    return size;
}
