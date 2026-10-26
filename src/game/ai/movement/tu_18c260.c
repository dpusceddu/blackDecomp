#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/movement_views.h"





extern s32 func_0018C368();
extern s32 func_0018C3C0(Recovered_MovementSelection*, Recovered_MovementRequest*, u32, s32);
extern void func_0018C688(Recovered_MovementSelection*, void*);
extern void func_0018CC20(void*, void*);
extern void func_001A73F0(void*);
extern void func_00182318(void*, s8);
extern void func_00188148(void*, s8);
extern s32 func_0035CA74(s32, const char*);

void func_0018C260(void *arg0)
{
  void *new_var;
  s32 temp_3;
  void *temp_16;
  void *temp_3_2;
  void *temp_3_3;
  temp_3 = M2C_FIELD(arg0, s32 *, 0xF8);
  if (temp_3 < 2)
  {
    new_var = arg0 + (temp_3 * 4);
    temp_16 = *((void **) (((s8 *) new_var) + 0xF0));
    temp_3_2 = *((void **) (((s8 *) temp_16) + 4));
    (*((M2C_UNK (**)(void *)) (((s8 *) temp_3_2) + 0x14)))(temp_16 + (M2C_FIELD(temp_3_2, s16 *, 0x10)));
    temp_3_3 = *((void **) (((s8 *) temp_16) + 4));
    if ((*((s32 (**)(void *)) (((s8 *) temp_3_3) + 0x34)))(temp_16 + (M2C_FIELD(temp_3_3, s16 *, 0x30))) != 0)
    {
      func_0018C368(arg0);
    }
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C2D8);
#ifdef NON_MATCHING
// Unmatched: saved-register allocation for selection and request differs.
s32 func_0018C2E0(Recovered_MovementSelection* self, Recovered_MovementRequest* request, u32 value, s32 arg3) {
    s32 result = func_0018C3C0(self, request, value, arg3);
    if (result) {
        switch (request->unk_00) {
        case 0:
            func_0018C688(self, request->data);
            break;
        case 1:
            func_0018CC20((u8*)self + 0x70, request->data);
            break;
        }
        result = request->unk_00;
        self->unk_100 = value;
        self->unk_F8 = result;
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C2E0);
#ifdef NON_MATCHING
// Unmatched: virtual-call register allocation differs.
s32 func_0018C368(Recovered_MovementSelection* self) {
    s32 index = self->unk_F8;
    s32 result = index * 4;
    if (index < 2) {
        Recovered_MovementChild* child = self->children[index];
        Recovered_MovementChildTable* table = child->table;
        table->unk_2C((u8*)child + table->unk_28);
        result = 2;
        self->unk_F8 = 2;
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C368);
#ifdef NON_MATCHING
// Unmatched: virtual-call return join and scheduling differ.
s32 func_0018C3C0(Recovered_MovementSelection* self, Recovered_MovementRequest* request, u32 value, s32 arg3) {
    s32 index = self->unk_F8;
    s32 result = 1;
    if (index != 2) {
        Recovered_MovementChild* child = self->children[index];
        Recovered_MovementChildTable* table = child->table;
        result = table->unk_34((u8*)child + table->unk_30);
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C3C0);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C688);
void func_0018C878(void** self) {
    u8* actor = *(u8**)((u8*)*self + 0x7C);
    void* component;
    *(s8*)(actor + 0x3AB) = 1;
    component = *(void**)(actor + 0x330);
    *(s8*)(actor + 0x3AF) = 0;
    func_001A73F0(component);
    func_00182318((u8*)*self + 0x810, 1);
    func_00188148((u8*)*self + 0x290, 0);
}

s32 func_0018C8D8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34) == 3;
}

#ifdef NON_MATCHING
// Unmatched: return-branch layout differs.
s32 func_0018C8E8(void* self, s32 value) {
    s32 count = M2C_FIELD(self, s32*, 0x34);
    if (count >= 3) return 3;
    if (count > 0) return func_0035CA74(value, M2C_FIELD(self, const char**, 0x30)) == 0;
    return 0;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018C938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18c260", func_0018CC20);
