#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern void func_001880D8(void *);
extern void func_00193980(void);
extern void *func_0013D400(void *);
extern s32 func_00172620(void *);
extern void func_00195920(void *);
extern void func_00173640(f32 *, f32);
extern void func_00181F48(void *, s32, s32, f32, f32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195710", func_00195710);
void func_00195860(void **action) {
    void *handler;
    func_00193980();
    handler = func_0013D400(*action);
    M2C_FIELD(action, s32 *, 8) = 0;
    M2C_FIELD(action, s32 *, 0xC) = func_00172620(handler);
    func_00195920(action);
    func_00173640((f32 *) ((u8 *) action + 0x10), 4.0f);
    M2C_FIELD(M2C_FIELD(*action, void **, 0x694), u8 *, 0x30) = 0;
    func_00181F48((u8 *) *action + 0xC80, 0, 0x1A, 0.0f, 2.0f);
}

void func_001958E0(void **arg0)
{
  int new_var2;
  void *temp_3;
  int new_var;
  func_00193988();
  new_var = 0;
  new_var2 = 0x290;
  temp_3 = *arg0;
  if ((*((u8 *) (temp_3 + new_var2))) != new_var)
  {
    func_001880D8(temp_3 + new_var2);
  }
}

void func_00195920(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
    if ((temp_3 != 0) && (temp_3 != M2C_FIELD(arg0, s32 *, 8))) {
        M2C_FIELD(arg0, s32 *, 8) = temp_3;
    }
}
