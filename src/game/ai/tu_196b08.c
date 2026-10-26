#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern void func_001880D8(void *);
extern void func_00193980(void);
extern void func_00182410(void *, s128, u8, u8);
extern s32 func_00185FE8(void *);
extern void func_00173690(f32 *);
extern void func_00196CF0(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_196b08", func_00196B08);
void func_00196C40(void **action) {
    u8 *owner;
    func_00193980();
    owner = *action;
    func_00182410(owner + 0x810, *(s128 *) func_00185FE8(owner + 0x90), 0, 0);
    M2C_FIELD(M2C_FIELD(*action, void **, 0x694), u8 *, 0x30) = 0;
    func_00173690((f32 *) ((u8 *) action + 8));
    func_00196CF0(action);
}

void func_00196CB0(void **arg0)
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_196b08", func_00196CF0);
