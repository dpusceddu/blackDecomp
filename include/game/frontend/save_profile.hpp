#ifndef GAME_FRONTEND_SAVE_PROFILE_HPP
#define GAME_FRONTEND_SAVE_PROFILE_HPP

/* Serialized profile records, distinct from the runtime snapshot view. */
struct FrontendSaveProfileFields {
    unsigned int unk_00;
    unsigned char unk_04[0xC4];
    unsigned int sortKey; // UNVERIFIED: semantic name comes from the native selection draft.
    unsigned char unk_CC[4];
    unsigned char displayAndPayload[0x69D]; // Starts with 16-bit display text; its complete extent is UNVERIFIED.
    unsigned char empty; // UNVERIFIED: interpreted by the native validation draft.
    unsigned char unk_76E[10];
};
struct FrontendSaveProfile {
    union {
        unsigned long words[239];
        FrontendSaveProfileFields fields;
    };
};
typedef char FrontendSaveProfileRecordSize[sizeof(FrontendSaveProfile) == 0x778 ? 1 : -1];
typedef char FrontendSaveProfileSortOffset[(unsigned)&((FrontendSaveProfile*)0)->fields.sortKey == 0xC8 ? 1 : -1];
typedef char FrontendSaveProfileEmptyOffset[(unsigned)&((FrontendSaveProfile*)0)->fields.empty == 0x76D ? 1 : -1];
#endif
