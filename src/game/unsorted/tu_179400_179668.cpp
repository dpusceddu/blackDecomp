#include "game/draft_views.hpp"

namespace Game { namespace DraftViews {

unsigned TableWord(void* object, int index) {
    unsigned* table = Field<unsigned*>(object, 0x70);
    table += index;
    return *table;
}

} }
