#include "include_asm.h"

#include "game/frontend/save_dialog.hpp"

extern "C" int func_00275260(const char *, void *, int);
extern "C" void func_0010B4D8(void *, int);

void FrontendSaveDialog::SetMessage(const char* text)
{
  short changed;
  changed = 1;
  message[0] = 0;
  message[1] = 0;
  if (text != 0)
  {
    func_00275260(text, message, 0x188);
    timeout = 3.2f;
  }
  else
  {
    timeout = 0;
    func_0010B4D8(this, 0);
  }
  flags[2] = changed;
  slot = -1;
}

#include "game/frontend/save_dialog.hpp"
extern "C" void func_0010B338(void*,const short*);
extern "C" void func_0010B3A8(void*,const short*,const short*,const short*,const short*);
extern "C" void func_0010B4D8(void*,int);
void FrontendSaveDialog::ClearMessage() { func_0010B338(this,0);func_0010B3A8(this,0,0,0,0);func_0010B4D8(this,0);flags[3]=0;slot=-1;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B3A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B4E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B630);

#ifdef NON_MATCHING
// Unmatched: state fallthrough scheduling and register allocation.
#include "ps2/prelude.h"
#include "game/frontend/save_dialog.hpp"
#include "ps2/recovered_types.h"

extern "C" s32 func_0026F440(s32 *);
extern "C" s32 func_0010BC00(void*);
extern "C" s32 func_0010F260(void *);
extern "C" void * D_0040F4EC;
extern "C" s32 func_0010B618(void *, s32);
extern "C" s32 func_0010B338(void *, char *);
extern "C" s32 func_0010B3A8(void *, char *, char *, char *, char *);
extern "C" s32 func_0010B4D8(void *, s32);
extern "C" s32 func_0010B530(void *, void *);
extern "C" s32 func_0010B6B8(void *);
extern "C" s32 func_0010B9B0(void *);

int FrontendSaveDialog::Enter() {
 char* arg0=(char*)this;
    s32 temp_3;
    s32 var_4;
    s32 var_4_2;
    char *temp_3_2;
    char *temp_3_3;
    char *temp_5;
    char *temp_6;

    temp_3 = phase;
    switch (temp_3) {                               /* irregular */
    case 0x1:
        func_0026F440((s32*)(arg0 + 0x9B0));
        temp_6 = arg0 + 0x528;
        temp_5 = arg0 + 0x52B;
        var_4 = 0;
        do {
            temp_3_2 = temp_5 + var_4;
            M2C_FIELD((temp_6 + var_4), char *, 0) = 0;
            var_4 += 1;
            *temp_3_2 = 0;
        } while (var_4 < 3);
        M2C_FIELD(arg0, char *, 8) = 0;
        func_0010BC00(arg0);
        phase = 0x38;
        /* fallthrough */
    case 0x38:
        mode = 0;
        var_4_2 = 0;
        loadState = 0;
        selectState = 0;
        saveState = 0;
        overwriteState = 0;
        disableState = 0;
        createState = 0;
        enableState = 0;
        do {
            temp_3_3 = arg0 + 0x52B + var_4_2;
            M2C_FIELD((arg0 + 0x528 + var_4_2), char *, 0) = 0;
            var_4_2 += 1;
            *temp_3_3 = 0;
        } while (var_4_2 < 3);
        func_0010F260(D_0040F4EC);
        phase = 2;
        /* fallthrough */
    case 0x2:
        profileBytes = 0x1668;
        phase = 3;
        /* fallthrough */
    case 0x3:
        func_0010B618(arg0, 0);
        itemCount = 0;
        selected = 0;
        M2C_FIELD(arg0, char *, 0x512) = 0;
        M2C_FIELD(arg0, char *, 0x513) = 0;
        M2C_FIELD(arg0, char *, 0x510) = 0;
        M2C_FIELD(arg0, char *, 0x514) = 0;
        M2C_FIELD(arg0, char *, 0x517) = 0;
        requested = 0;
        M2C_FIELD(arg0, s32 *, 0x504) = 0;
        activeSlot = -1;
        slot = -1;
        M2C_FIELD(arg0, char *, 0x515) = 1;
        func_0010B338(arg0, 0);
        func_0010B3A8(arg0, 0, 0, 0, 0);
        selected = 0;
        if (itemCount <= 0) {
            selected = 0;
        }
        func_0010B4D8(arg0, 0);
        func_0010B530(arg0, 0);
        M2C_FIELD(arg0, s16 *, 0x44A) = 0;
        M2C_FIELD(arg0, s16 *, 0x44C) = 0;
        func_0010B6B8(arg0);
        func_0010B9B0(arg0);
        requestedSlot = 0;
        phase = 6;
        break;
    }
    phase = 0x1C;
    return 1;
}
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B6B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B7F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B8B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010B9B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010BA00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010BA78);
