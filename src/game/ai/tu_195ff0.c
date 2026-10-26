#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/action_views.h"

extern s32 func_00193988();
extern void func_001880D8(void *);
extern s32 func_00188F10(void *);
extern f32 func_00189310(void *);
extern u8 func_00188350(void *);
extern void func_00193990(void *, u8);
extern void func_00196168(void *);
extern void func_0017E428(void *, s128);
extern s128 func_00189048(void *);
extern void func_00186E40(void *);
extern void func_00193980(void);
extern void func_00187FE0(void *, s32);
extern s32 func_00185FE8(void *);

void func_00195FF0(Recovered_ActionMove *action) {
    if (!func_00188F10(action->owner + 0x150)) goto failed;
    if (func_00189310(action->owner + 0x150) > 3.0f) goto failed;
    if (func_00188350(action->owner + 0x290) == 0) goto active;
    func_00186E40(action->owner + 0x90);
failed:
    func_00193990(action, 0);
    return;
active:
    if (M2C_FIELD(action->owner, u8 *, 0x291)) {
        func_00193990(action, 1);
        return;
    }
    func_00196168(action);
    {
        s128 position = func_00189048(action->owner + 0x150);
        func_0017E428(action->owner + 0x650, position);
    }
}
void func_001960C8(Recovered_ActionMove *action) {
    func_00193980();
    func_00187FE0(action->owner + 0x290, 0);
    M2C_FIELD(M2C_FIELD(action->owner, void **, 0x694), u8 *, 0x30) = 0;
    action->position = *(s128 *) func_00185FE8(action->owner + 0x90);
    func_00196168(action);
}

void func_00196128(void **arg0)
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195ff0", func_00196168);
