#include "include_asm.h"

#include "game/effects/mod_asset_views.hpp"

BkActorAssetRecordPS2 *ModEffects::Timer::Resolve(BkActorAssetPS2 *asset){if(index!=-1)return &asset->records[index];return 0;}

