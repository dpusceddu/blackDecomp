#include "include_asm.h"
#include "sony/osd_config.h"

extern char D_003C15F8[14];
extern s16 D_003C15F0;
extern u8 D_003C15F2;
extern u8 D_003C15F4;
extern u8 D_003C15F6;
extern s32 func_0036BD20(const char* path, s32 flags);
extern s32 func_0036C368(s32 fd, void* buffer, s32 count);
extern s32 func_0036BFB0(s32 fd);
extern void GetOsdConfigParam(Recovered_OsdConfig* config);
extern void GetOsdConfigParam2(void* config, s32 size, s32 offset);

typedef struct {
    char path[12];
} __attribute__((aligned(8))) RomVersionPath;
static const RomVersionPath romVersionPath = {"rom0:ROMVER"};

char* RomVersion_Read(void) {
    if (D_003C15F8[0] == 0) {
        s32 fd = func_0036BD20(romVersionPath.path, 1);
        if (fd >= 0) {
            func_0036C368(fd, D_003C15F8, 14);
            func_0036BFB0(fd);
        }
    }
    return D_003C15F8;
}

s32 RomVersion_IsTool(void) {
    if (D_003C15F8[0] == 0) { RomVersion_Read(); }
    return D_003C15F8[4] == 'T';
}

s32 OsdConfig_GetLanguage(void) {
    Recovered_OsdConfig config;
    s32 language;
    GetOsdConfigParam(&config);
    if (RomVersion_IsTool()) {
        language = D_003C15F4;
    } else {
        GetOsdConfigParam(&config);
        if (config.version == 0)
            language = config.japanLanguage;
        else
            language = config.language;
    }
    return language;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29cee8", func_0029CFF8);

s32 OsdConfig_GetScreenType(void) {
    Recovered_OsdConfig config;
    if (RomVersion_IsTool()) { return D_003C15F2; }
    GetOsdConfigParam(&config);
    return config.screenType;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29cee8", func_0029D040);

s32 OsdConfig_GetTimezone(void) {
    Recovered_OsdConfig config;
    s32 timezone;
    if (RomVersion_IsTool())
        timezone = D_003C15F0;
    else {
        GetOsdConfigParam(&config);
        if (config.version == 0)
            timezone = 540;
        else
            timezone = config.timezoneMinutes;
    }
    return timezone;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29cee8", func_0029D098);

#ifdef NON_MATCHING
// Unmatched: extended-byte extraction uses a different result register.
s32 OsdConfig_IsDaylightSavingEnabled(void) {
    struct {
        u8 unk_0 : 4;
        u8 daylightSaving : 1;
        u8 unk_5 : 3;
    } extended;
    Recovered_OsdConfig config;
    u8 daylight;
    if (RomVersion_IsTool())
        daylight = D_003C15F6;
    else {
        GetOsdConfigParam(&config);
        if (config.version == 0)
            daylight = 0;
        else {
            GetOsdConfigParam2(&extended, 1, 1);
            daylight = extended.daylightSaving;
        }
    }
    return daylight;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29cee8", func_0029D0A0);
#endif
