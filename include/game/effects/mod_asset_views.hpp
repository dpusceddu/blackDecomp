#ifndef BLACK_EFFECTS_MOD_ASSET_VIEWS_HPP
#define BLACK_EFFECTS_MOD_ASSET_VIEWS_HPP
#include "game/effects/asset.h"

namespace ModEffects {
// Descriptive access views; historical class identities remain unverified.
class Timer : public BkActorTimerPS2 {
public:
    BkActorAssetRecordPS2 *Resolve(BkActorAssetPS2 *);
    void Advance(BkActorAssetPS2 *, int);
    int Start(BkActorAssetPS2 *, int);
};
class Asset : public BkActorAssetPS2 {
public:
    int FindFree();
    void Relocate();
};
struct Region { char opaque[0x38]; };
struct Regions {
    Region regions[3];
    void Initialize();
    int Resize();
};
}
#endif
