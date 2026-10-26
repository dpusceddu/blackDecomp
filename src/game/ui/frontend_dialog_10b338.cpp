#include "include_asm.h"
#include "game/frontend/save_dialog.hpp"

extern "C" s32 func_00275340(const unsigned short* text);
extern "C" void* D_0040F4EC;
extern "C" void* D_0040F4C4;
extern "C" FrontendSaveDialog* D_0040F4F0;
extern "C" void func_0010F288(void*, void*, s32);
extern "C" void func_0010F648(void*);
extern "C" const FrontendSaveProfile* func_0010F280(void*);
extern "C" s32 func_0010F680(const FrontendSaveProfile*);
extern "C" s32 func_0010BBF0(const FrontendSaveProfile*);
extern "C" s32 func_0010B160(FrontendSaveDialog*);
extern "C" void* func_001092F8(void*);
extern "C" s32 func_00109300(void*);
extern "C" void func_0010BAE0(FrontendSaveDialog*, void*, s32);
extern "C" void func_00108540(void*, s32, void*, s32);

static inline void SetSelection(FrontendSaveDialog* self, int index) {
    self->selected = index;
    if (self->itemCount <= 0) self->selected = 0;
}

static inline FrontendSaveProfile* ProfileAt(FrontendSaveDialog* self, int index) {
    u32 address = index * sizeof(FrontendSaveProfile) + (u32)self;
    return (FrontendSaveProfile*)(address + (u32) & ((FrontendSaveDialog*)0)->profiles);
}

static inline u32 RequiredSpace(int** lengths, u32 quantum) {
    u32 blocks = 4;
    u32 index;
    for (index = 0; index < 3; ++index) blocks += ((u32)*lengths[index] + quantum - 1) / quantum;
    return blocks * quantum;
}

void FrontendSaveDialog::SetMessage(const char* text)
{
  short changed;
  changed = 1;
  message[0] = 0;
  message[1] = 0;
  if (text != 0)
  {
    Text_CopyUtf8ToUtf16(text, message, 0x188);
    timeout = 3.2f;
  }
  else
  {
    timeout = 0;
    SetChoice(0);
  }
  flags[2] = changed;
  slot = -1;
}

void FrontendSaveDialog::SetOptions(const char* first, const char* second, const char* third, const char* fourth) {
    unsigned int index;
    itemCount = 0;
    for (index = 0; index < 4; ++index) {
        details[index][0] = 0;
        details[index][1] = 0;
    }
    if (first) {
        Text_CopyUtf8ToUtf16(first, details[0], 32);
        ++itemCount;
    }
    if (second) {
        Text_CopyUtf8ToUtf16(second, details[1], 32);
        ++itemCount;
    }
    if (third) {
        Text_CopyUtf8ToUtf16(third, details[2], 32);
        ++itemCount;
    }
    if (fourth) {
        Text_CopyUtf8ToUtf16(fourth, details[3], 32);
        ++itemCount;
    }
    if (itemCount) {
        flags[3] = 1;
        timeout = 0;
    } else
        SetChoice(0);
    SetSelection(this, 0);
    slot = -1;
}

int FrontendSaveDialog::SetLabel(const char* text) {
    label[0] = 0;
    label[1] = 0;
    int result;
    if (text) {
        Text_CopyUtf8ToUtf16(text, label, 20);
        result = func_00275340(label) > 0;
    } else {
        result = 0;
    }
    return result;
}

void FrontendSaveDialog::ClearMessage() { SetMessage(0);SetOptions(0,0,0,0);SetChoice(0);flags[3]=0;slot=-1;}

#ifdef NON_MATCHING
// Unmatched: Profile-index address arithmetic is strength-reduced differently.
int FrontendSaveDialog::FindNewestProfile() {
    int found = 0;
    int selectedIndex = 0;
    int index;
    unsigned int newest;
    unsigned int* sortKey = &profiles[0].fields.sortKey;
    for (index = 0; index < 3; ++index, sortKey = (u32*)((u8*)sortKey + sizeof(FrontendSaveProfile))) {
        if (available[index] && !corrupt[index]) {
            if (!found) {
                found = 1;
                newest = *sortKey;
                selectedIndex = index;
            } else {
                FrontendSaveProfile* candidate = ProfileAt(this, index);
                if (newest < candidate->fields.sortKey) {
                    selectedIndex = index;
                    newest = candidate->fields.sortKey;
                }
            }
        }
    }
    return selectedIndex;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/frontend_dialog_10b338", func_0010B630);
#endif

void FrontendSaveDialog::InitializeProfiles() {
    int index;
    func_0010F288(D_0040F4EC, 0, 1);
    func_0010F648(D_0040F4EC);
    for (index = 0; index < 3; ++index) {
        FrontendSaveProfile* destination = ProfileAt(this, index);
        *destination = *func_0010F280(D_0040F4EC);
    }
    ValidateProfiles();
}

void FrontendSaveDialog::CheckProfileDataSize() {
    int index;
    if (status != sizeof(profileData)) {
        for (index = 0; index < 3; ++index) {
            available[index] = 1;
            corrupt[index] = 1;
            profiles[index].fields.unk_00 = 0;
        }
    }
}

#ifdef NON_MATCHING
// Unmatched: Profile and flag cursors use different registers and shared branch joins.
void FrontendSaveDialog::ValidateProfiles() {
    int index;
    FrontendSaveProfile* profile = profiles;
    for (index = 0; index < 3; ++index, ++profile) {
        if (func_0010F680(profile) == 1) {
            if (profile->fields.empty) {
                available[index] = 0;
            } else {
                int supported = func_0010BBF0(&profiles[0]);
                available[index] = 1;
                if (supported != 1) goto markCorrupt;
            }
            corrupt[index] = 0;
        } else {
            available[index] = 1;
        markCorrupt:
            corrupt[index] = 1;
        }
        if (corrupt[index] == 1) profile->fields.unk_00 = 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/frontend_dialog_10b338", func_0010B7F0);
#endif

const unsigned short* FrontendSaveDialog::ProfileLabel(int index) {
    if (!available[index]) return slotLabels.empty;
    const unsigned short* result;
    if (!corrupt[index])
        result = (const unsigned short*)ProfileAt(this, index)->fields.displayAndPayload;
    else
        result = slotLabels.corrupt;
    return result;
}

#ifdef NON_MATCHING
// Unmatched: Compiler merges the native separate error-status return paths.
int FrontendSaveDialog::PollResult() {
    s32 result;
    s32 current;
    SaveIo_Poll(&ioState, 0, &result);
    if (flags[3] == 1) {
        if (slot >= 0 && slot < itemCount) func_0010B160(this);
    } else if (flags[4] == 1) {
        if (slot >= 0) func_0010B160(this);
    }
    current = SaveIo_GetStatus(&ioState.reportedStatus);
    switch (current) {
        case 13: return SaveIo_GetError(&ioState);
        case 0: return 0;
        default: return SaveIo_GetError(&ioState);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/frontend_dialog_10b338", func_0010B8E8);
#endif

int FrontendSaveDialog::CalculateRequiredSpace() { return requiredBytes = RequiredSpace(fileLengths, 1024); }

extern "C" void FrontendSave_EncodeFullWidth(void*, unsigned short* output, const char* input) {
    int code = *input;
    while (code) {
        if ((u32)(code - 'a') < 26)
            *output = ((code + 0x20) << 8) | 0x82;
        else if ((u32)(code - 'A') < 26 || (u32)(code - '0') < 10)
            *output = ((code + 0x1F) << 8) | 0x82;
        else if (code == ' ')
            *output = 0x4081;
        else
            *output = 0;
        ++input;
        code = *input;
        ++output;
    }
    *output = 0;
}

extern "C" void FrontendSave_OnResourceLoaded(void* source) {
    void* data = func_001092F8(source);
    s32 size = func_00109300(source);
    func_0010BAE0(D_0040F4F0, data, size);
    func_00108540(D_0040F4C4, 13, data, 0);
}

#ifdef NON_MATCHING
// Unmatched: state fallthrough scheduling and register allocation.
#include "ps2/prelude.h"
#include "game/frontend/save_dialog.hpp"
#include "ps2/recovered_types.h"

extern "C" s32 func_0010BC00(void*);
extern "C" s32 func_0010F260(void *);
extern "C" void * D_0040F4EC;
extern "C" s32 func_0010B618(void *, s32);
extern "C" s32 func_0010B530(void *, void *);

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
        SaveIo_Initialize(&ioState);
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
        SetMessage(0);
        SetOptions(0, 0, 0, 0);
        selected = 0;
        if (itemCount <= 0) {
            selected = 0;
        }
        SetChoice(0);
        func_0010B530(arg0, 0);
        M2C_FIELD(arg0, s16 *, 0x44A) = 0;
        M2C_FIELD(arg0, s16 *, 0x44C) = 0;
        InitializeProfiles();
        CalculateRequiredSpace();
        requestedSlot = 0;
        phase = 6;
        break;
    }
    phase = 0x1C;
    return 1;
}
#endif
