#ifndef GAME_FRONTEND_SAVE_DIALOG_HPP
#define GAME_FRONTEND_SAVE_DIALOG_HPP

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
    char details[6][0x40];
    unsigned short label[20];
    short reserved4f2;
    int itemCount, selected, choice, slot;
    float timeout, previousTime;
    int requestedSlot;
    unsigned char flags[8];
    unsigned char ioError;
    char reserved519[3];
    int profileBytes, status, activeSlot;
    unsigned char available[3], readOnly[3];
    char filename[0x20], directory[0x20];
    char reserved56e[2];
    int reserved570, requested, fileCount;
    char* fileNames[3];
    int* fileLengths[3];
    void* fileData[3];
    char iconName[0x20], secondaryName[0x20];
    int reserved5e0, counter;
    FrontendSaveImage image;
    int imageBytes;
    char io[0x1a0];
    char profileData[0x1668];
    void BeginDelete() __asm__("func_0010B1C8");
    void BeginSave() __asm__("func_0010B238");
    void BeginFormat() __asm__("func_0010B200");
    void BeginSelect() __asm__("func_0010B270");
    void SetMessage(const char*) __asm__("func_0010B338");
    void ClearMessage() __asm__("func_0010B5B0");
    void UpdateOperation() __asm__("func_0010B018");
    int Enter() __asm__("func_0010AA70");
    void UpdateIO() __asm__("func_0010EBD0");
    void Initialize() __asm__("func_0010A870");
};
typedef char FrontendSaveImageSize[(sizeof(FrontendSaveImage)==0x3c4)?1:-1];
#endif
