#ifndef GAME_FRONTEND_PROFILE_SNAPSHOT_HPP
#define GAME_FRONTEND_PROFILE_SNAPSHOT_HPP

// PS2 settings and profile views, recovered from save/load assignments.
struct FrontendProfileSettings {
    int sound, music, control;
    float sensitivity, vertical, horizontal;
    unsigned char enabled, option19, reserved1a, option1b, option1c;
    char reserved1d[7];
    unsigned char option24;
    char reserved25[3];
    int progress[37];
};
struct FrontendProfileData {
    int count;
    char reserved4[0x6a1];
    unsigned char valid;
    short reserved6a6;
} __attribute__((aligned(8)));
struct FrontendProfilePool {
    FrontendProfileData* selected;
    int reserved4;
    FrontendProfileData entries[1];
    void Initialize() __asm__("func_0010F188");
    int Reset() __asm__("func_0010F1E0");
};
struct FrontendProfileGlobal {
    char reserved[0x2014c];
    FrontendProfileSettings settings;
};
struct FrontendProfileSnapshot {
    int checksum, count;
    unsigned char valid;
    char reserved9[3];
    float previousTime, currentTime;
    int reserved14, version, bytes;
    FrontendProfileSettings settings;
    int reserveddc;
    FrontendProfileData data;
    int storedChecksum;
    int Reset() __asm__("func_0010F260");
    void Capture(void*,int) __asm__("func_0010F288");
    void Apply() __asm__("func_0010F470");
    void Remember() __asm__("func_0010F620");
};
typedef char FrontendProfileSettingsSize[(sizeof(FrontendProfileSettings)==0xbc)?1:-1];
typedef char FrontendProfileDataSize[(sizeof(FrontendProfileData)==0x6a8)?1:-1];
#endif
