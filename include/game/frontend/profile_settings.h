#ifndef GAME_FRONTEND_PROFILE_SETTINGS_H
#define GAME_FRONTEND_PROFILE_SETTINGS_H

/* PS2 settings view recovered from save/load assignments. Unaccessed field
 * identities remain UNVERIFIED. */
typedef struct FrontendProfileSettings {
    int sound, music, control;
    float sensitivity, vertical, horizontal;
    unsigned char enabled, option19, reserved1a, option1b, option1c;
    char reserved1d[7];
    unsigned char option24;
    char reserved25[3];
    int progress[37];
} FrontendProfileSettings;

typedef char FrontendProfileSettingsSize[(sizeof(FrontendProfileSettings) == 0xBC) ? 1 : -1];

#endif
