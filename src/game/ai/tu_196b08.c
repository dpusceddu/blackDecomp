#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor_records.h"

extern s32 func_00193988();
extern void func_001880D8(void *);
extern void func_00193980(void);
extern void func_00182410(void *, s128, u8, u8);
extern s32 func_00185FE8(void *);
extern void func_00173690(f32 *);
extern void func_00196CF0(void *);

extern u8 func_001829A8(void*);
extern s32 func_001829E8(void*);
extern s32 func_00188F10(Recovered_ActorRecords*);
extern s32 func_0018AB08(Recovered_ActorRecords*);
extern void func_00186E40(void*);
extern void func_00193990(void*, u8);
extern f32 func_001891A8(void*);
extern s32 func_00173610(f32*);
extern void func_0017E428(void*, s128);
extern s128 func_00189048(Recovered_ActorRecords*);

void func_00196B08(void** action) {
    void* owner;
    void* component;

    if (func_001829A8((void*)(((s8*)(*action)) + 0x810)) != 0) {
        if (func_001829E8((void*)(((s8*)(*action)) + 0x810)) != 0) {
            if (func_00188F10((Recovered_ActorRecords*)(((s8*)(*action)) + 0x150)) == 0) { goto request_one; }
            if (func_0018AB08((Recovered_ActorRecords*)(((s8*)(*action)) + 0x150)) == 0) {
                component = (void*)(((s8*)(*action)) + 0x90);
                if (M2C_FIELD(component, u8*, 0x81) != 0) { func_00186E40(component); }
            request_zero:
                func_00193990((void*)action, 0U);
                return;
            }
        request_one:
            func_00193990((void*)action, 1U);
            return;
        }
        if ((func_00188F10((Recovered_ActorRecords*)(((s8*)(*action)) + 0x150)) != 0) &&
            (func_0018AB08((Recovered_ActorRecords*)(((s8*)(*action)) + 0x150)) != 0) &&
            (func_001891A8((void*)(((s8*)(*action)) + 0x150)) < 15.0f) &&
            (func_00173610((f32*)((void*)(((s8*)action) + 8))) != 0)) {
            owner = (*action);
            func_0017E428((f32*)(((s8*)owner) + 0x650), func_00189048((Recovered_ActorRecords*)(((s8*)owner) + 0x150)));
        }
        func_00196CF0(action);
        return;
    } else {
        goto request_zero;
    }
}
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
