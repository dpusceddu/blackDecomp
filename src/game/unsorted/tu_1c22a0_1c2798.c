#include "include_asm.h"
#include "ps2/prelude.h"

void func_001C2798(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2)
{
  s8 *new_var;
  s8 *new_var2;
  new_var2 = (s8 *) arg0;
  if ((M2C_FIELD(arg0, s32 *, 0x34)) == 0)
  {
    new_var = (s8 *) arg0;
    M2C_FIELD(arg0, f32 *, 0x24) = fparg2;
    *((s32 *) (new_var2 + 0x34)) = 1;
    *((f32 *) (new_var + 0x18)) = 1.0f;
    *((f32 *) (new_var + 0x1C)) = fparg0;
    *((s32 *) (new_var + 0x14)) = 0;
    *((f32 *) (new_var + 0x20)) = fparg1;
    *((s32 *) (new_var + 0x38)) = 0;
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2798", func_001C27D0);

void func_001C2838(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_3 != 9) {
        M2C_FIELD(arg0, f32 *, 0x30) = fparg2;
        M2C_FIELD(arg0, s32 *, 0x38) = temp_3;
        M2C_FIELD(arg0, s32 *, 0x34) = 2;
        M2C_FIELD(arg0, f32 *, 0x18) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x28) = fparg0;
        M2C_FIELD(arg0, f32 *, 0x2C) = fparg1;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2798", func_001C2878);

s32 func_001C28A0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34) == 1;
}

extern s32 func_001C29C0(void*, const s32*);
extern void* D_0040F4C0;
extern void func_001C88C8(void*, void*);
extern void func_001AF768(s32, s32);
extern void func_001C2A18(void*);

void func_001C28B0(void* object, const s32* coordinates) {
    s32 previousX;
    s32 previousY;
    void* context;
    void* position;

    func_001C29C0(object, coordinates);
    context = M2C_FIELD(M2C_FIELD(D_0040F4C0, void**, 0xD540), void**, 0x58);
    position = M2C_FIELD(context, void**, 0x60);
    previousX = M2C_FIELD(position, s32*, 0xC);
    M2C_FIELD(position, s32*, 0xC) = (s32)M2C_FIELD(coordinates, s32*, 0);
    previousY = M2C_FIELD(position, s32*, 0x10);
    M2C_FIELD(M2C_FIELD(context, void**, 0x60), s32*, 0x10) = (s32)M2C_FIELD(coordinates, s32*, 4);
    func_001C88C8((void*)(((s8*)D_0040F4C0) + 0xCFD0), context);
    func_001AF768((s32)((void*)(((s8*)D_0040F4C0) + 0x14)), 4);
    M2C_FIELD(M2C_FIELD(context, void**, 0x60), s32*, 0xC) = previousX;
    M2C_FIELD(M2C_FIELD(context, void**, 0x60), s32*, 0x10) = previousY;
    func_001C88C8((void*)(((s8*)D_0040F4C0) + 0xCFD0), context);
    func_001C2A18(object);
}
