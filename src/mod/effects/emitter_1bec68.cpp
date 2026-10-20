#include "game/effects/mod_emitter_methods.hpp"
int ModEffects::Flights::Clear() {
    u32 i = 0, j;
    do {
        BkModAttachedEffectPS2 *record = records + i;
        record->active = 0;
        j = 0;
        BkModEffectChildrenPS2 *child = &record->children;
        do {
            child->items[j] = 0;
            j = (j + 1) & 0xFFFF;
        } while (j < 8);
        i = (i + 1) & 0xFFFF;
        child->resource = 0;
    } while (i < 44);
    return 1;
}
