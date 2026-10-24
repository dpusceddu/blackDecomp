#include "game/effects/asset.h"
typedef BkActorAssetRecordPS2 BkFlagRecordPS2;
typedef BkActorAssetPS2 BkFlagAssetPS2;
extern "C" int func_001AFBF0(void *);

extern "C" bool func_001AFBA8(BkFlagAssetPS2 *asset) {
    BkFlagRecordPS2 *record = &asset->records[func_001AFBF0(asset)];
    if (record) return (record->flags5a >> 5) & 1;
    return false;
}

extern "C" bool func_001AFC30(BkFlagAssetPS2 *asset) {
    BkFlagRecordPS2 *record = &asset->records[func_001AFBF0(asset)];
    if (record) return (record->flags58 >> 14) & 1;
    return false;
}
