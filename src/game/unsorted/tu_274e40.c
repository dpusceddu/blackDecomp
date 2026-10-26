#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/aligned_buffer.h"

typedef struct { u32 unk_00[4]; } Recovered_AllocatorHookSnapshot;
extern Recovered_AlignedBuffer* D_003C09E0;
extern Recovered_AllocatorHookSnapshot D_0049A780;
extern Recovered_AllocatorHookSnapshot* func_002A65E0(void);
extern s32 (*D_00449544)();

s32 func_00274E40(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 0) = 0;
    return func_00274F58(arg0, 4);
}

s32 AlignedBuffer_Bind(Recovered_AlignedBuffer* self, void* buffer, u32 bytes) {
    s32 success = 1;
    self->cursor = buffer;
    self->begin = buffer;
    self->end = (u8*)buffer + bytes;
    AlignedBuffer_SetAlignment(self, 4);
    self->unk_00 = success;
    return success;
}

void func_00274EA8(void *arg0)
{
  s32 temp_4;
  int new_var2;
  s32 *new_var;
  new_var = (s32 *) (((s8 *) arg0) + 4);
  if (arg0 == D_003C09E0)
  {
    AlignedBuffer_RestoreAllocatorHooks();
  }
  temp_4 = *new_var;
  if (temp_4 != 0)
  {
    new_var2 = 4;
    D_00449544(temp_4);
    *((s32 *) (((s8 *) arg0) + new_var2)) = 0;
  }
 do { M2C_FIELD(arg0, s8 *, 0) = 0; M2C_FIELD(arg0, s32 *, 8) = 0; } while (0);
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
}

void AlignedBuffer_RestoreAllocatorHooks(void) {
    *func_002A65E0() = D_0049A780;
    D_003C09E0 = NULL;
}

void func_00274F58(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}

s32 func_00274F60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 8);
}

s32 func_00274F70(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0x10);
}
