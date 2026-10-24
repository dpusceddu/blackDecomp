#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
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
