#include "include_asm.h"

#include "game/effects/asset_views.hpp"

BkActorAssetRecordPS2 *Effects::Timer::Resolve(BkActorAssetPS2 *asset){if(index!=-1)return &asset->records[index];return 0;}

