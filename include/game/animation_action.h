#ifndef BLACK_GAME_ANIMATION_ACTION_H
#define BLACK_GAME_ANIMATION_ACTION_H
#include "ps2/ee_types.h"

/* Action storage consumed by AnimationViews::Owner::RequestAction.
 * Original identities and gameplay meanings of individual values are UNVERIFIED. */
typedef struct {
    EeS32 kind, key;
    float value;
    EeS32 mode;
    EeU8 flag;
} Recovered_AnimationAction;
typedef char AnimationActionExtent[sizeof(Recovered_AnimationAction) == 20 ? 1 : -1];
#endif
