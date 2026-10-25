#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: global address reuse and save-image loop scheduling.
#include "ps2/prelude.h"
#include "game/frontend/save_dialog.hpp"
#include "ps2/recovered_types.h"

extern "C" s32 func_0035D728(void *, char *, ...);
extern "C" char* D_003BC5F8;
extern "C" char* D_003BC5EC;
extern "C" char* D_003BC5F0;
extern "C" void * func_0035C6EC(void *, s32, s32);
extern "C" char * func_0035CBC0(char *,const char*);
extern "C" s32 func_0010BA00(void *, void *, void *);
extern "C" char* D_003BC5F4;
extern "C" void func_0010BBF8(void);

void FrontendSaveDialog::Initialize() {
    char* arg0=(char*)this;
    char *temp_16;
    u32 var_4;


    activeSlot = -1;
    mode = 0;
    profileBytes = 0;
    requestedSlot = 0;
    M2C_FIELD(arg0, char *, 0x510) = 0;
    previousTime = 0;
    M2C_FIELD(arg0, char *, 8) = 0;
    func_0035D728(arg0 + 0x52E, "%s", D_003BC5F8);
    temp_16 = "%s/%s";
    func_0035D728(arg0 + 0x54E, temp_16, D_003BC5F8, D_003BC5F8);
    func_0035D728(arg0 + 0x5C0, temp_16, D_003BC5F8, D_003BC5EC);
    func_0035D728(arg0 + 0x5A0, temp_16, D_003BC5F8, D_003BC5F0);
    func_0035C6EC(arg0 + 0x5E8, 0, 0x3C4);
    M2C_FIELD(arg0, s32 *, 0x9AC) = 0x3C4;
    M2C_FIELD(arg0, char *, 0x5E9) = 0x53;
    var_4 = 0;

    M2C_FIELD(arg0, char *, 0x5E8) = 0x50;
    M2C_FIELD(arg0, char *, 0x5EA) = 0x32;
    M2C_FIELD(arg0, char *, 0x5EB) = 0x44;
    M2C_FIELD(arg0, s16 *, 0x5EE) = 0x12;
    do {
        image.indices[0][var_4] = 0;

        image.indices[1][var_4] = 0;
        image.indices[2][var_4] = 0;
        image.indices[3][var_4] = 0;
        image.indices[4][var_4] = 0;
        image.indices[5][var_4] = 0;
        image.vectors[0][var_4] = -1.0f;
        image.vectors[1][var_4] = 1.0f;
        image.vectors[2][var_4] = 1.0f;
        image.vectors[3][var_4] = 1.0f;
        image.vectors[4][var_4] = 0.5f;

        ++var_4;
    } while (var_4 < 4U);
    func_0035CBC0(arg0 + 0x6EC, D_003BC5EC);
    func_0035CBC0(arg0 + 0x72C, D_003BC5EC);
    func_0035CBC0(arg0 + 0x76C, D_003BC5EC);
    func_0010BA00(arg0, arg0 + 0x6A8, D_003BC5F4);
    M2C_FIELD(arg0, s32 *, 0x5E0) = 0;
    M2C_FIELD(arg0, s32 *, 0x5E4) = 0;
    M2C_FIELD(arg0, s32 *, 0x59C) = 0;
    M2C_FIELD(arg0, s32 *, 0x570) = 0;
    M2C_FIELD(arg0, void **, 0x57C) = (void *) (arg0 + 0x54E);
    M2C_FIELD(arg0, void **, 0x588) = (void *) (arg0 + 0x51C);
    M2C_FIELD(arg0, void **, 0x594) = (void *) (arg0 + 0xB50);
    M2C_FIELD(arg0, void **, 0x580) = (void *) (arg0 + 0x5A0);
    M2C_FIELD(arg0, void **, 0x58C) = (void *) (arg0 + 0x9AC);
    M2C_FIELD(arg0, void **, 0x598) = (void *) (arg0 + 0x5E8);
    M2C_FIELD(arg0, void **, 0x584) = (void *) (arg0 + 0x5C0);
    M2C_FIELD(arg0, void **, 0x590) = (void *) (arg0 + 0x5E4);
    M2C_FIELD(arg0, s32 *, 4) = 1;
    M2C_FIELD(arg0, s32 *, 0x578) = 1;
    func_0010BBF8();
}
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35b470_35c6ec", func_0035C6EC);
