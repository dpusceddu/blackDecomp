#ifndef GAME_FRONTEND_SAVE_DIALOG_HPP
#define GAME_FRONTEND_SAVE_DIALOG_HPP

#include "game/frontend/save_profile.hpp"
#include "game/frontend/save_io.h"

struct FrontendSaveSlotLabels {
    unsigned char unk_00[0x178];
    const unsigned short* empty;
    const unsigned short* corrupt;
    unsigned char unk_180[0x20];
};

// Field views verified against the PS2 save-dialog accesses; behavior names are inferred.
struct FrontendSaveImage {
    char magic[4];
    char reserved4[2];
    short version;
    char reserved8[8];
    int indices[6][4];
    float vectors[5][4];
    char reservedc0[0x304];
};
struct FrontendSaveDialog {
    int state, phase;
    unsigned char initialized;
    char reserved9[3];
    int mode, loadState, selectState, saveState, overwriteState;
    int deleteState, formatState, enableState, disableState;
    int createState, operation;
    unsigned char exists, reserved39;
    unsigned short message[0x188];
    unsigned short details[6][0x20];
    unsigned short label[20];
    short reserved4f2;
    int itemCount, selected, choice, slot;
    float timeout, previousTime;
    int requestedSlot;
    unsigned char flags[8];
    unsigned char ioError;
    char reserved519[3];
    int profileBytes, status, activeSlot;
    unsigned char available[3], corrupt[3];
    char filename[0x20], directory[0x20];
    char reserved56e[2];
    int requiredBytes, requested, fileCount;
    char* fileNames[3];
    int* fileLengths[3];
    void* fileData[3];
    char iconName[0x20], secondaryName[0x20];
    int reserved5e0, counter;
    FrontendSaveImage image;
    int imageBytes;
    union {
        char io[0x1a0];
        Recovered_SaveIo ioState;
        FrontendSaveSlotLabels slotLabels;
    };
    union {
        char profileData[0x1668];
        FrontendSaveProfile profiles[3];
    };
    void BeginDelete() __asm__("func_0010B1C8");
    void BeginSave() __asm__("func_0010B238");
    void BeginFormat() __asm__("func_0010B200");
    void BeginSelect() __asm__("func_0010B270");
    void SetOptions(const char*, const char*, const char*, const char*) __asm__("FrontendSaveDialog_SetOptions");
    int SetLabel(const char*) __asm__("FrontendSaveDialog_SetLabel");
    int FindNewestProfile() __asm__("FrontendSaveDialog_FindNewestProfile");
    void InitializeProfiles() __asm__("FrontendSaveDialog_InitializeProfiles");
    void CheckProfileDataSize() __asm__("FrontendSaveDialog_CheckProfileDataSize");
    void ValidateProfiles() __asm__("FrontendSaveDialog_ValidateProfiles");
    const unsigned short* ProfileLabel(int slot) __asm__("FrontendSaveDialog_ProfileLabel");
    int PollResult() __asm__("FrontendSaveDialog_PollResult");
    int CalculateRequiredSpace() __asm__("FrontendSaveDialog_CalculateRequiredSpace");
    void SetChoice(int value) __asm__("FrontendSaveDialog_SetChoice");
    void SetMessage(const char*) __asm__("FrontendSaveDialog_SetMessage");
    void ClearMessage() __asm__("FrontendSaveDialog_ClearMessage");
    void UpdateOperation() __asm__("func_0010B018");
    int Enter() __asm__("func_0010AA70");
    void UpdateIO() __asm__("func_0010EBD0");
    void Initialize() __asm__("func_0010A870");
};
typedef char FrontendSaveImageSize[(sizeof(FrontendSaveImage)==0x3c4)?1:-1];
typedef char FrontendSaveIoStorageSize[sizeof(FrontendSaveSlotLabels) == 0x1A0 ? 1 : -1];
typedef char FrontendSaveProfilesOffset[(unsigned)&((FrontendSaveDialog*)0)->profiles == 0xB50 ? 1 : -1];
extern "C" void Text_CopyUtf8ToUtf16(const char* text, unsigned short* output, int capacity);
#endif
