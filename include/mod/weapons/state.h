#ifndef BLACK_MOD_WEAPON_STATE_H
#define BLACK_MOD_WEAPON_STATE_H
#include "ps2/ee_types.h"
/* Partial PS2 access views, not original class identities or allocation sizes.
   Native controls 156DC0 and 158078..1580E0 verify the fields they use.
   Other named fields below remain PS2 instruction leads until a control consumes them. */
typedef struct BkModWeaponDefinitionPS2 {
    EeU8 unknown00[0x60];
    EeS32 capacity, reserveIndex;
    EeU8 unknown68[0x38];
    struct BkModWeaponDefinitionPS2 *secondary; /* A0:15D060/15D248 instruction evidence only. */
    EeU8 unknowna4[0x20];
    EeU8 flagC4, unknownC5[2], perRound;
} BkModWeaponDefinitionPS2;
typedef struct BkModWeaponOwnerPS2 {
    EeU8 unknown00[0xc4]; EeS32 kind;
} BkModWeaponOwnerPS2;
typedef struct BkModWeaponTimingPS2 {
    EeU8 unknown00[0x20]; float elapsed;
} BkModWeaponTimingPS2;
struct BkModWeaponControllerPS2;
typedef struct BkModWeaponInstancePS2 {
    EeU32 unknown00;
    struct BkModWeaponControllerPS2 *weapon;
    BkModWeaponDefinitionPS2 *definition;
    BkModWeaponTimingPS2 *timing;
    void *effect;
    EeS32 burstCount;
    EeS16 clip;
    EeU8 unknown1a[6];
    EeS8 mode;
} BkModWeaponInstancePS2;
typedef struct BkModWeaponControllerPS2 {
    EeS8 weaponId; EeU8 unknown01[0xd7];
    EeS32 phase;
    float cooldown, elapsed;
    EeU8 unknownE4[8];
    BkModWeaponDefinitionPS2 *definition;
    BkModWeaponOwnerPS2 *owner;
    BkModWeaponInstancePS2 *primary, *secondary;
    void *inventory;
    EeU8 flags100[0xb];
    EeS8 outOfAmmo;
} BkModWeaponControllerPS2;
static inline EeS32 BkModWeaponReloadingPS2(const BkModWeaponControllerPS2 *weapon) { return weapon->phase == 4; }
static inline EeS16 BkModWeaponClipPS2(const BkModWeaponControllerPS2 *weapon) { return weapon->primary->clip; }
/* Capacity is read as signed32 in eligibility, low8 for some transfer requests,
   and low16 for other stores. These consumers must retain their individual widths. */
typedef char BkModWeaponPhaseD8[(unsigned)&((BkModWeaponControllerPS2*)0)->phase==0xd8?1:-1];
typedef char BkModWeaponPrimaryF4[(unsigned)&((BkModWeaponControllerPS2*)0)->primary==0xf4?1:-1];
typedef char BkModWeaponClip18[(unsigned)&((BkModWeaponInstancePS2*)0)->clip==0x18?1:-1];
#endif
