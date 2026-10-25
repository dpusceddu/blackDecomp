#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0026F7E0(s32, M2C_UNK, M2C_UNK);
extern s32 func_00275340(void *);
extern s32 func_00275398(void *, M2C_UNK, void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10a870", func_0010A870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10a870", func_0010AA70);

#include "ps2/recovered_types.h"
extern void * func_0035C6EC(void *, s32, s32);
extern s8 * func_001087C8(void *, void *);
extern s32 D_0040F4C4;

s32 func_0010AC48(void *arg0) {
    s8 *temp_4;

    temp_4 = M2C_FIELD(arg0, s8 **, 0xA8C);
    func_0035C6EC(temp_4, 0, M2C_FIELD(arg0, s8 **, 0xB4C) - temp_4);
    M2C_FIELD(arg0, s8 **, 0xB28) = func_001087C8((void *) D_0040F4C4, "FE_MCOption_ProfileEmpty");
    M2C_FIELD(arg0, s8 **, 0xB2C) = func_001087C8((void *) D_0040F4C4, "FE_MCOption_ProfileCorrupt");
    M2C_FIELD(arg0, s8 **, 0xB38) = func_001087C8((void *) D_0040F4C4, "FE_MCOption_Yes");
    M2C_FIELD(arg0, s8 **, 0xB3C) = func_001087C8((void *) D_0040F4C4, "FE_MCOption_No");
    M2C_FIELD(arg0, s8 **, 0xB40) = func_001087C8((void *) D_0040F4C4, "FE_MCOption_Continue");
    M2C_FIELD(arg0, s8 **, 0xB44) = func_001087C8((void *) D_0040F4C4, "FE_MCOption_Retry");
    M2C_FIELD(arg0, s8 **, 0xB48) = func_001087C8((void *) D_0040F4C4, "FE_MCTitle_LoadProfile");
    M2C_FIELD(arg0, s8 **, 0xB4C) = func_001087C8((void *) D_0040F4C4, "FE_MCTitle_SaveProfile");
    M2C_FIELD(arg0, s8 **, 0xACC) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_AskConfirm");
    M2C_FIELD(arg0, s8 **, 0xAEC) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_AskOverwrite");
    M2C_FIELD(arg0, s8 **, 0xAF0) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_AskSave");
    M2C_FIELD(arg0, s8 **, 0xAF4) = func_001087C8((void *) D_0040F4C4, "FE_MCContinueNoSaveConfirm");
    M2C_FIELD(arg0, s8 **, 0xAF8) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_AskSaveProfileName");
    M2C_FIELD(arg0, s8 **, 0xAC0) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_Failed_CorruptData");
    M2C_FIELD(arg0, s8 **, 0xB0C) = func_001087C8((void *) D_0040F4C4, "FE_MCAutosaveWillBeDisabled");
    M2C_FIELD(arg0, s8 **, 0xB14) = func_001087C8((void *) D_0040F4C4, "FE_MCAskEnableAutosave");
    M2C_FIELD(arg0, s8 **, 0xB18) = func_001087C8((void *) D_0040F4C4, "FE_MCAskDisableAutosave");
    M2C_FIELD(arg0, s8 **, 0xB1C) = func_001087C8((void *) D_0040F4C4, "FE_MCNewProfile_Confirm");
    M2C_FIELD(arg0, s8 **, 0xB20) = func_001087C8((void *) D_0040F4C4, "FE_MCNewProfile_EnableAutosave");
    M2C_FIELD(arg0, s8 **, 0xB24) = func_001087C8((void *) D_0040F4C4, "FE_MCNewProfile_EnableAutosaveConfirm");
    M2C_FIELD(arg0, s8 **, 0xA8C) = func_001087C8((void *) D_0040F4C4, "FE_MCCheckingCard");
    M2C_FIELD(arg0, s8 **, 0xA90) = func_001087C8((void *) D_0040F4C4, "FE_MCBoot_NoCard");
    M2C_FIELD(arg0, s8 **, 0xA94) = func_001087C8((void *) D_0040F4C4, "FE_MCBoot_NoSpace");
    M2C_FIELD(arg0, s8 **, 0xA98) = func_001087C8((void *) D_0040F4C4, "FE_MCFormat_Formatting");
    M2C_FIELD(arg0, s8 **, 0xA9C) = func_001087C8((void *) D_0040F4C4, "FE_MCFormat_Success");
    M2C_FIELD(arg0, s8 **, 0xAA0) = func_001087C8((void *) D_0040F4C4, "FE_MCFormat_Failed");
    M2C_FIELD(arg0, s8 **, 0xAA4) = func_001087C8((void *) D_0040F4C4, "FE_MCFormat_Failed_CardRemoved");
    M2C_FIELD(arg0, s8 **, 0xAA8) = func_001087C8((void *) D_0040F4C4, "FE_MCFormat_AskConfirm");
    M2C_FIELD(arg0, s8 **, 0xAAC) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_Loading");
    M2C_FIELD(arg0, s8 **, 0xAB0) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_NoCard");
    M2C_FIELD(arg0, s8 **, 0xAB4) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_NoFile");
    M2C_FIELD(arg0, s8 **, 0xAB8) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_Success");
    M2C_FIELD(arg0, s8 **, 0xABC) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_Failed");
    M2C_FIELD(arg0, s8 **, 0xAC8) = func_001087C8((void *) D_0040F4C4, "FE_MCLoad_Failed_CardRemoved");
    M2C_FIELD(arg0, s8 **, 0xAD0) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_Saving");
    M2C_FIELD(arg0, s8 **, 0xAD4) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_NoCard");
    M2C_FIELD(arg0, s8 **, 0xAD8) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_NoSpace");
    M2C_FIELD(arg0, s8 **, 0xADC) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_NotFormatted");
    M2C_FIELD(arg0, s8 **, 0xAE0) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_Success");
    M2C_FIELD(arg0, s8 **, 0xAE4) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_Failed");
    M2C_FIELD(arg0, s8 **, 0xAE8) = func_001087C8((void *) D_0040F4C4, "FE_MCSave_Failed_CardRemoved");
    M2C_FIELD(arg0, s8 **, 0xAFC) = func_001087C8((void *) D_0040F4C4, "FE_MCAutosave_Saving");
    M2C_FIELD(arg0, s8 **, 0xB00) = func_001087C8((void *) D_0040F4C4, "FE_MCAutosave_Failed");
    M2C_FIELD(arg0, s8 **, 0xB04) = func_001087C8((void *) D_0040F4C4, "FE_MCAutosave_Failed_CardRemoved");
    M2C_FIELD(arg0, s8 **, 0xB08) = func_001087C8((void *) D_0040F4C4, "FE_MCAutosave_Failed_WrongCard");
    M2C_FIELD(arg0, s8 *, 8) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10a870", func_0010B018);

s32 func_0010B160(s32 arg0) {
    s32 temp_16;
    s32 var_3;

    temp_16 = arg0 + 0x9B0;
    var_3 = func_0026F7E0(temp_16, 0, 0);
    if ((var_3 != 0) && (var_3 != 0xD)) {
        var_3 = func_0026F7E0(temp_16, 1, 0);
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_10a870", func_0010B1B8);

void func_0010B2A8(void *arg0)
{
  s8 *new_var;
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 1;
  arg0 += 0;
  new_var = (s8 *) arg0;
 do { *((s32 *) (new_var + 0x10)) = 0; } while (0);
}

void func_0010B2C0(void *arg0, s8 arg1)
{
  M2C_FIELD(arg0, s8 *, 0x517) = arg1;
  if ((arg1 && arg1) && arg1)
  {
  }
  M2C_FIELD(arg0, s32 *, 0xC) = 5;
 M2C_FIELD(arg0, s32 *, 0x1C) = 0; M2C_FIELD(arg0, s8 *, 0x515) = 0;
}

void func_0010B2D8(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 9;
}

void func_0010B2F0(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0x2C) = 0;
  *((s32 *) (0xC + ((s8 *) arg0))) = 6;
}

void func_0010B308(void *arg0)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 0x515;
  M2C_FIELD(arg0, s32 *, 0x30) = (*((s8 *) new_var) = 0);
  M2C_FIELD(arg0, s32 *, 0xC) = 7;
}

s32 func_0010B320(s32 arg0) {
    return arg0 + 0x3A;
}

void * func_0010B328(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 << 6) + 0x34A);
}


void func_0010B4D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x4FC) = arg1;
}


s32 func_0010B530(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s16 *, 0x4CA) = 0;
    M2C_FIELD(arg0, s16 *, 0x4CC) = 0;
    if ((arg1 != NULL) && (func_00275340(arg1) > 0)) {
        func_00275398(arg0 + 0x4CA, 0x14, arg1);
        return 1;
    }
    return 0;
}

s32 func_0010B590(s32 arg0) {
    return func_00275340(arg0 + 0x4CA) > 0;
}


void func_0010B608(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x500) = arg1;
}

u8 func_0010B610(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x515);
}

void func_0010B618(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x516) = arg1;
}

s32 func_0010B620(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x4F8);
    M2C_FIELD(arg0, s32 *, 0x4F8) = 0;
    return temp_2;
}
