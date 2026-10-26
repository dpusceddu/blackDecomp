#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern void func_00193980(void);
extern s32 func_00181028();
extern s32 func_00180FE0();
extern void func_001880D8(void *);
extern s32 func_00185F00();

/* Partial action view; class identity and full extent are unknown. */
typedef struct Recovered_AIAction {
    u8* owner;
    u8 unk_04[4];
    u8 unk_08;
} Recovered_AIAction;
extern void* func_00193B98(Recovered_AIAction*);
extern s32 func_0019ACB8(Recovered_AIAction*);
extern void func_00193A28(Recovered_AIAction*, u32, void*);
extern s16 func_001580E0(void*);
extern s32 func_00188F10(void*);
extern void func_0019AC18(void**);

s32 func_0019A930(Recovered_AIAction* self) {
    func_00193980();
    M2C_FIELD(func_00193B98(self), s32*, 0x3C) = 0;
    M2C_FIELD(func_00193B98(self), s32*, 0) = 2;
    M2C_FIELD(func_00193B98(self), f32*, 0x64) = 2.0f;
    M2C_FIELD(func_00193B98(self), s32*, 0x5C) = 0;
    M2C_FIELD(self->owner, u8*, 0x104) = 1;
    M2C_FIELD(self->owner, u8*, 0x110) = 1;
    M2C_FIELD(M2C_FIELD(self->owner, void**, 0x694), u8*, 0x35) = 1;
    self->unk_08 = 0;
    return func_0019ACB8(self);
}

void func_0019A9C0(void **arg0)
{
  s8 *new_var;
  void *temp_3;
  func_00193988();
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    temp_3 = (*arg0) + 0x140;
    func_00180FE0(temp_3);
  }
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
}

#ifdef NON_MATCHING
// Unmatched: switch branch scheduling and jump-table ownership differ.
void func_0019AA20(Recovered_AIAction* self, s32 event, s32 value) {
    u32 next;
    switch (event) {
    case 0x3B:
        if (value) goto dispatch;
        next = 0x16;
        goto transition;
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
        if (func_001580E0(M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), void**, 0x2A4)) < 3) goto fallback;
        if (value) goto fallback;
        if (func_00188F10(self->owner + 0x150)) next = 0x3B;
        else next = 0x16;
        goto transition;
fallback:
        func_0019AC18((void**)self);
        return;
    case 0xA:
        next = 3;
transition:
        func_00193A28(self, next, NULL);
        return;
    case 3:
    case 7:
    case 8:
    case 0xD:
    case 0x16:
dispatch:
        func_0019ACB8(self);
        return;
    case 0x1A:
        self->unk_08 = 0;
        func_0019ACB8(self);
        return;
    default:
        return;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19a930", func_0019AA20);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19a930", func_0019AB10);

void func_0019AC18(void **arg0)
{
  void *temp_3;
  void *new_var;
  temp_3 = *arg0;
  new_var = temp_3 + 0x290;
  if ((M2C_FIELD(temp_3, u8 *, 0x290)) != 0)
  {
    func_001880D8(new_var);
  }
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    func_00180FE0((*arg0) + 0x140);
  }
  if (!((((u8) (*((u8 *) (((s8 *) (*arg0)) + 0xD60)))) >> 4) & 1))
  {
    goto block_9;
  }
  if (func_00185F00((*arg0) + 0x90) != 0)
  {
    func_00193A28(arg0, 0xA, (void *) 0);
    return;
  }
  block_9:
  func_00193A28(arg0, 3, (void *) 0);

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19a930", func_0019ACB8);
