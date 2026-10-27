#include "game/draft_views.hpp"
#include "game/stream_control.h"

namespace Game {
namespace DraftViews {

void* SelectedRecord(void* object) {
    Recovered_StreamControl* self = static_cast<Recovered_StreamControl*>(object);
    int index;
    if (self->state != 0x1C || (index = self->selected) < 0) {
        return 0;
    }
    return &self->records[index];
}

}
}
