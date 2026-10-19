#ifndef BLACK_CAMPAIGN_ACTOR_VIEWS_HPP
#define BLACK_CAMPAIGN_ACTOR_VIEWS_HPP
#include "classes/game/UnknownVtable_003DC838.hpp"
#include "classes/game/UnknownVtable_003DCC20.hpp"
#include "classes/game/UnknownVtable_003DC5F8.hpp"

namespace BlackPS2Campaign {
// Class identity and complete size are not established. These views retain the
// PS2 offsets recovered from this class's callers and virtual-method table.
struct ActorEntries : BlackPS2Classes::UnknownVtable_003DC838 {
    struct Entry { unsigned char active, pending, a, b, c, d; };
    inline Entry * Entries() { return (Entry *)Field_01A8(); }
    inline unsigned char & Field_01ED() { return *(unsigned char *)((char *)this + 0x1ed); }
    inline unsigned char Count() { return Field_01F5(); }
    void Update(float delta);
    int ResetEntries(int reason);
};
}
#endif
