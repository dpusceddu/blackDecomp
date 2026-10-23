#define BLACK_PS2 1
#include "game/ai_movement_modes_decls.hpp"
namespace BlackGame {
PositionResult RouteMode::GetTarget() const
{
    if (active) {
        bool completed = active->kind == 9;
        if (completed) {
            if (!arrived) {
                if (state == 4 || state == 5) {
                    int cursor = follower->cursor;
                    if (cursor < active->PointCount()) return RoutePointAt(active, cursor);
                }
                return AsResult(active->destination);
            }
        }
    }
    return AsResult(target);
}
}
