#ifndef BLACK_GAME_AUDIO_SOUND_OBJECT_FIELDS_H
#define BLACK_GAME_AUDIO_SOUND_OBJECT_FIELDS_H

#include "ps2/ee_types.h"

/* PS2 sound-object access view; the caller advances objects by 0x430 bytes.
 * UNVERIFIED: original class identity and the contents of untouched gaps. */
typedef struct RecoveredSoundObject {
    unsigned char unknown00[0x60];
    int field60;
    unsigned char unknown64[0x10];
    float field74;
    unsigned char unknown78[0xc];
    int field84;
    unsigned char unknown88[0x148];
    int field1d0, field1d4, field1d8, field1dc;
    void* field1e0;
    int field1e4, field1e8;
    int field1ec[2];
    unsigned char field1f4;
    unsigned char unknown1f5[0x1b];
    short field210[0x100];
    void* field410;
    int field414;
    float field418;
    unsigned char field41c;
    unsigned char unknown41d[7];
    float field424;
    unsigned char unknown428[8];
} RecoveredSoundObject;

typedef char RecoveredSoundObjectSize[sizeof(RecoveredSoundObject) == 0x430 ? 1 : -1];

#endif
