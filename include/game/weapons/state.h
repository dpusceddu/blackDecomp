#ifndef BLACK_MOD_WEAPON_STATE_H
#define BLACK_MOD_WEAPON_STATE_H
#include "ps2/ee_types.h"
/* Partial PS2 access views, not original class identities or allocation sizes.
   Matched functions 156DC0 and 158078..1580E0 verify the fields they use.
   Other named fields below remain PS2 instruction leads until a control consumes them. */
typedef struct BkWeaponDefinitionPS2 {
    EeU8 unknown00[0x60];
    EeS32 capacity, reserveIndex;
    EeU8 unknown68[0x38];
    struct BkWeaponDefinitionPS2 *secondary; /* A0:pointer access verified by function 15D248. */
    EeU8 unknowna4[0x20];
    EeU8 flagC4, unknownC5[2], perRound;
} BkWeaponDefinitionPS2;
typedef struct BkWeaponOwnerPS2 {
    EeU8 unknown00[0xc4]; EeS32 kind;
} BkWeaponOwnerPS2;
typedef struct BkWeaponTimingPS2 {
    EeU8 unknown00[0x20]; float elapsed;
} BkWeaponTimingPS2;
struct BkWeaponControllerPS2;
typedef struct BkWeaponInstancePS2 {
    EeU32 unknown00;
    struct BkWeaponControllerPS2 *weapon;
    BkWeaponDefinitionPS2 *definition;
    BkWeaponTimingPS2 *timing;
    void *effect;
    EeS32 burstCount;
    EeS16 clip;
    EeU8 unknown1a[6];
    EeS8 mode;
} BkWeaponInstancePS2;
typedef struct BkWeaponControllerPS2 {
    EeS8 weaponId; EeU8 unknown01[0xd7];
    EeS32 phase;
    float cooldown, elapsed;
    EeU8 unknownE4[8];
    BkWeaponDefinitionPS2 *definition;
    BkWeaponOwnerPS2 *owner;
    BkWeaponInstancePS2 *primary, *secondary;
    void *inventory;
    EeU8 flags100[0xb];
    EeS8 outOfAmmo;
} BkWeaponControllerPS2;
static inline EeS32 BkWeaponReloadingPS2(const BkWeaponControllerPS2 *weapon) { return weapon->phase == 4; }
static inline EeS16 BkWeaponClipPS2(const BkWeaponControllerPS2 *weapon) { return weapon->primary->clip; }
/* Capacity is read as signed32 in eligibility, low8 for some transfer requests,
   and low16 for other stores. These consumers must retain their individual widths. */
typedef char BkWeaponPhaseD8[(unsigned)&((BkWeaponControllerPS2*)0)->phase==0xd8?1:-1];
typedef char BkWeaponPrimaryF4[(unsigned)&((BkWeaponControllerPS2*)0)->primary==0xf4?1:-1];
typedef char BkWeaponClip18[(unsigned)&((BkWeaponInstancePS2*)0)->clip==0x18?1:-1];
#endif
