#ifndef SONY_OSD_CONFIG_H
#define SONY_OSD_CONFIG_H
#include "ps2/prelude.h"

/* Native settings used by the development TOOL and retail OSD accessors.
 * Field meanings agree with PS2SDK's ConfigParamT10K and ConfigParam.
 * https://github.com/ps2dev/ps2sdk/blob/master/ee/kernel/src/osd_config.c */
typedef struct {
    s16 timezoneMinutes;
    u8 screenType;
    u8 unk_03;
    u8 language;
    u8 unk_05;
    u8 daylightSaving;
    u8 unk_07;
} Recovered_ToolOsdConfig;

typedef struct {
    u32 unk_00 : 1;
    u32 screenType : 2;
    u32 unk_03 : 1;
    u32 japanLanguage : 1;
    u32 unk_05 : 8;
    u32 version : 3;
    u32 language : 5;
    s32 timezoneMinutes : 11;
} Recovered_OsdConfig;

typedef char OsdConfigWordSize[sizeof(Recovered_OsdConfig) == 4 ? 1 : -1];
typedef char ToolOsdConfigSize[sizeof(Recovered_ToolOsdConfig) == 8 ? 1 : -1];

char* RomVersion_Read(void);
s32 RomVersion_IsTool(void);
s32 OsdConfig_GetLanguage(void);
s32 OsdConfig_GetScreenType(void);
s32 OsdConfig_GetTimezone(void);
s32 OsdConfig_IsDaylightSavingEnabled(void);
#endif
